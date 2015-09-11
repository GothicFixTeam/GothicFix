#include "PreCompiled.h"

#include <io.h>
#include <fcntl.h>

#include <d3d9.h>
#pragma comment(lib, "d3d9.lib")

void RedirectIOToConsole(void)
{
	int hConHandle;
	long lStdHandle;
	CONSOLE_SCREEN_BUFFER_INFO coninfo;
	FILE *fp;

	// allocate a console for this app
	AllocConsole();

	// set the screen buffer to be big enough to let us scroll text
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &coninfo);
	coninfo.dwSize.Y = 50;
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), coninfo.dwSize);

	// redirect unbuffered STDOUT to the console
	lStdHandle = (long)GetStdHandle(STD_OUTPUT_HANDLE);
	hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);

	fp = _fdopen( hConHandle, "w" );
	//_dup2(_fileno(fp), _fileno(stdout));
	*stdout = *fp;
	setvbuf(stdout, NULL, _IONBF, 0);

	// redirect unbuffered STDERR to the console
	lStdHandle = (long)GetStdHandle(STD_ERROR_HANDLE);
	hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);

	fp = _fdopen( hConHandle, "w" );
	//_dup2(_fileno(fp), _fileno(stderr));
	*stderr = *fp;
	setvbuf(stderr, NULL, _IONBF, 0);
}

bool GetModuleFileNameString(HMODULE hModule, TString& name)
{
	SetLastError(ERROR_INSUFFICIENT_BUFFER);
	for(uInt i = 1; GetLastError() == ERROR_INSUFFICIENT_BUFFER; i++)
	{
		name.Resize(i * MAX_PATH);
		SetLastError(0);
		if(!GetModuleFileName(hModule, (TCHAR*)name.GetData(), i * MAX_PATH))
			return false;
	}
	return (name.Length() != 0);
}

bool GetGothicWindowSize(POINT& size)
{
	size.x = size.y = 0;

	char Buffer[256];
	GothicReadIniString("VIDEO", "zVidResFullscreenX", "0", Buffer, 256, "Gothic.ini");
	size.x = atoi(Buffer);
	GothicReadIniString("VIDEO", "zVidResFullscreenY", "0", Buffer, 256, "Gothic.ini");
	size.y = atoi(Buffer);

	return (size.x && size.y);
}

bool IsVdfs(void)
{
	TString ExeName;
	if(GetModuleFileNameString(GetModuleHandle(NULL), ExeName))
	{
		ExeName.TruncateBeforeLast(_T("\\"));
		return ExeName.Compare(_T("vdfs32"), true, 6);
	}
	return false;
}

bool IsSpacer(void)
{
	TString ExeName;
	if(GetModuleFileNameString(GetModuleHandle(NULL), ExeName))
	{
		ExeName.TruncateBeforeLast(_T("\\"));
		return ExeName.Compare(_T("spacer"), true, 6);
	}
	return false;
}

static bool		ExeCrcReaded = false;
static uLong	ExeCrc = 0;

uLong GetExeCrc32(void)
{
	if(!ExeCrcReaded)
	{
		ExeCrc = 0;

		TString ExeName;
		if(GetModuleFileNameString(NULL, ExeName))
		{
			FILE* fp = _tfopen(ExeName, _T("rb"));
			if(fp)
			{
				uChar Buffer[1024];
				size_t size = 0;
				while(size = fread(Buffer, 1, 1024, fp))
					ExeCrc = Crc32(Buffer, size, ExeCrc);
				ExeCrcReaded = true;
				fclose(fp);
			}
		}
	}

	return ExeCrc;
}

const uChar* GetSectionAddress(const uChar* codeBase, const char* name, size_t& size)
{
	size_t namelen = strlen(name);
	if(namelen > 8)
		return NULL;

	PIMAGE_DOS_HEADER dos_header = (PIMAGE_DOS_HEADER)codeBase;
	if(dos_header->e_magic != IMAGE_DOS_SIGNATURE) 
		return 0;

	PIMAGE_NT_HEADERS headers = (PIMAGE_NT_HEADERS)&((uChar*)dos_header)[dos_header->e_lfanew];
	PIMAGE_SECTION_HEADER section = IMAGE_FIRST_SECTION(headers);
	for(int i = 0; i < headers->FileHeader.NumberOfSections; i++, section++) 
	{
		if(!memcmp(section->Name, name, namelen))
		{
			size = section->SizeOfRawData;
			return codeBase + section->PointerToRawData;
		}
	}
	return NULL;
}

uLong GetSectionCrc32(const char* name)
{
	uLong Result = 0;

	size_t namelen = strlen(name);
	if(namelen > 8)
		return Result;

	TString ExeName;
	if(GetModuleFileNameString(NULL, ExeName))
	{
		FILE* fp = _tfopen(ExeName, _T("rb"));
		if(fp)
		{
			fseek(fp, 0, SEEK_END);
			long size = ftell(fp);
			fseek(fp, 0, SEEK_SET);

			if(!size)
			{
				fclose(fp);
				return Result;
			}

			uChar* Buffer = new uChar[size];
			size = fread(Buffer, 1, size, fp);
			fclose(fp);

			if(size)
			{
				const uChar* codeBase = Buffer;

				PIMAGE_DOS_HEADER dos_header = (PIMAGE_DOS_HEADER)codeBase;
				if(dos_header->e_magic != IMAGE_DOS_SIGNATURE) 
					return 0;

				PIMAGE_NT_HEADERS headers = (PIMAGE_NT_HEADERS)&((uChar*)dos_header)[dos_header->e_lfanew];
				PIMAGE_SECTION_HEADER section = IMAGE_FIRST_SECTION(headers);
				for(int i = 0; i < headers->FileHeader.NumberOfSections; i++, section++) 
				{
					if(!memcmp(section->Name, name, namelen))
					{
						if(section->SizeOfRawData != 0)
							Result = Crc32(codeBase + section->PointerToRawData, section->SizeOfRawData);
						break;
					}
				}
			}
			delete[] Buffer;
		}
	}
	return Result;
}

bool HasVgaVendor(DWORD ven)
{
	bool Result = false;
	IDirect3D9* D3D = Direct3DCreate9(D3D_SDK_VERSION);
	if(D3D)
	{
		for(UINT i = 0; i < D3D->GetAdapterCount(); i++)
		{
			D3DADAPTER_IDENTIFIER9 Adapter;
			if(SUCCEEDED(D3D->GetAdapterIdentifier(i, 0, &Adapter)))
			{
				if(Adapter.VendorId == ven)
				{
					Result = true;
					break;
				}
			}
		}
		D3D->Release();
	}
	return Result;
}

bool Patch(uChar* data, size_t size, uChar* org, uChar* patch)
{
	bool Result = false;

	DWORD OldProtect = 0;
	if(VirtualProtect(data, size, PAGE_READWRITE, &OldProtect))
	{
		if(!org || !memcmp(data, org, size))
		{
			memcpy(data, patch, size);
			Result = true;
		}
		else
		{
			RedirectIOToConsole();
			for(size_t i = 0; i < size; i++)
				printf("0x%X(%c), ", data[i], data[i]);
		}
		VirtualProtect(data, 5, OldProtect, &OldProtect);
	}

	return Result;
}

DWORD GetImportSize(const uChar* codeBase)
{
	PIMAGE_DOS_HEADER dos_header = (PIMAGE_DOS_HEADER)codeBase;
	if(dos_header->e_magic != IMAGE_DOS_SIGNATURE) 
		return 0;

	PIMAGE_NT_HEADERS old_header = (PIMAGE_NT_HEADERS)&codeBase[dos_header->e_lfanew];
	if (old_header->Signature != IMAGE_NT_SIGNATURE)
		return 0;

	return old_header->OptionalHeader.SizeOfImage;
}

PIMAGE_IMPORT_DESCRIPTOR GetImportDescriptor(const uChar* codeBase, const char* name)
{
	PIMAGE_DOS_HEADER dos_header = (PIMAGE_DOS_HEADER)codeBase;
	if(dos_header->e_magic != IMAGE_DOS_SIGNATURE) 
		return NULL;

	PIMAGE_NT_HEADERS old_header = (PIMAGE_NT_HEADERS)&codeBase[dos_header->e_lfanew];
	if (old_header->Signature != IMAGE_NT_SIGNATURE)
		return NULL;

	PIMAGE_DATA_DIRECTORY directory = &old_header->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];
	if (directory->Size > 0) 
	{
		PIMAGE_IMPORT_DESCRIPTOR importDesc = (PIMAGE_IMPORT_DESCRIPTOR) (codeBase + directory->VirtualAddress);
		for (; !IsBadReadPtr(importDesc, sizeof(IMAGE_IMPORT_DESCRIPTOR)) && importDesc->Name; importDesc++) 
		{
			LPCSTR Name = (LPCSTR)(codeBase + importDesc->Name);
			if(!_stricmp(Name, name))
				return importDesc;
		}
	}

	return NULL;
}

FARPROC* GetImportFunctionAddress(const uChar* codeBase, PIMAGE_IMPORT_DESCRIPTOR importDesc, bool ordinal, const char* name)
{
	DWORD* thunkRef = NULL;
	FARPROC* funcRef = NULL;

	if(importDesc->OriginalFirstThunk) 
	{
		thunkRef = (DWORD*)(codeBase + importDesc->OriginalFirstThunk);
		funcRef = (FARPROC*)(codeBase + importDesc->FirstThunk);
	} 
	else 
	{
		// no hint table
		thunkRef = (DWORD*)(codeBase + importDesc->FirstThunk);
		funcRef = (FARPROC*)(codeBase + importDesc->FirstThunk);
	}

	for(; *thunkRef; thunkRef++, funcRef++) 
	{
		if(IMAGE_SNAP_BY_ORDINAL(*thunkRef)) 
		{
			if(ordinal)
			{
				LPCSTR FuncOrdinal = (LPCSTR)IMAGE_ORDINAL(*thunkRef);
				if(!memcmp(FuncOrdinal, name, sizeof(DWORD)))
					return funcRef;
			}
		} 
		else
		{
			if(!ordinal)
			{
				PIMAGE_IMPORT_BY_NAME thunkData = (PIMAGE_IMPORT_BY_NAME)(codeBase + (*thunkRef));
				if(!_stricmp((LPCSTR)&thunkData->Name, name))
					return funcRef;
			}
		}
	}

	return NULL;
}