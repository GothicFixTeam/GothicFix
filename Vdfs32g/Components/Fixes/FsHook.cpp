#include "PreCompiled.h"

uInt CalcFileCrc(HANDLE hFile)
{
	uInt ResCrc = 0;
	DWORD Offset = SetFilePointer(hFile, 0, NULL, FILE_CURRENT);

	SetFilePointer(hFile, 0, NULL, FILE_BEGIN);

	uChar Buffer[0xFFFF];
	DWORD BufferSize = 0xFFFF;

	DWORD Readed = 0;
	while(ReadFile(hFile, (void*)Buffer, BufferSize, &Readed, NULL) && (Readed != 0))
		ResCrc = Crc32(Buffer, Readed, ResCrc);

	SetFilePointer(hFile, Offset, NULL, FILE_BEGIN);
	return ResCrc;
}

#pragma pack(push, 1)

struct FixFileInfo
{
uInt		Version;
FILETIME	LastWriteTime;
uInt		CRC;
};

#define FIX_FILE_INFO_VERSION 1

#pragma pack(pop)

uInt GetFileCrc(const TString& file)
{
	HANDLE hFile = CreateFile(file, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if(hFile != INVALID_HANDLE_VALUE)
	{
		HANDLE hFixCrcInfo = CreateFile(file + _T(":FixCrcInfo"), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
		if(hFixCrcInfo != INVALID_HANDLE_VALUE)
		{
			DWORD Readed = 0;

			FixFileInfo FileInfo;
			ReadFile(hFixCrcInfo, &FileInfo, sizeof(uInt), &Readed, NULL);
			if(FileInfo.Version == FIX_FILE_INFO_VERSION)
			{
				if(ReadFile(hFixCrcInfo, ((uInt*)&FileInfo) + 1, sizeof(FixFileInfo) - sizeof(uInt), &Readed, NULL))
				{
					FILETIME LastWriteTime = {};
					if(GetFileTime(hFile, NULL, NULL, &LastWriteTime))
					{
						if(!memcmp(&FileInfo.LastWriteTime, &LastWriteTime, sizeof(FILETIME)))
						{
							CloseHandle(hFixCrcInfo);
							CloseHandle(hFile);
							return FileInfo.CRC;
						}
					}
				}
			}
			CloseHandle(hFixCrcInfo);
		}

		FixFileInfo NewFileInfo;
		memset(&NewFileInfo, 0, sizeof(FixFileInfo));
		NewFileInfo.Version = 1;
		NewFileInfo.CRC = CalcFileCrc(hFile);
		if(GetFileTime(hFile, NULL, NULL, &NewFileInfo.LastWriteTime))
		{
			hFixCrcInfo = CreateFile(file + _T(":FixCrcInfo"), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);
			if(hFixCrcInfo != INVALID_HANDLE_VALUE)
			{
				DWORD Written = 0;
				WriteFile(hFixCrcInfo, &NewFileInfo, sizeof(FixFileInfo), &Written, NULL);
				SetFileTime(hFixCrcInfo, NULL, NULL, &NewFileInfo.LastWriteTime);
				CloseHandle(hFixCrcInfo);
			}
		}

		CloseHandle(hFile);
		return NewFileInfo.CRC;
	}
	return 0;
}

Vdfs* FS;
TaggedArray<AString, HANDLE> WriteFiles;

HANDLE WINAPI MyCreateFileA(LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile)
{
	HANDLE hFile = CreateFileA(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
	if((hFile != INVALID_HANDLE_VALUE) && ((dwDesiredAccess & GENERIC_ALL) || (dwDesiredAccess & GENERIC_WRITE)))
	{
		AString FileName(lpFileName);
		FileName.ToUpperCase();
		if(FileName.GetData("_WORK\\DATA"))
		{
			TString ExePath;
			if(PlatformGetExePath(ExePath))
			{
				ExePath.ToUpperCase();
				ExePath.TruncateAfterLast(_T("\\SYSTEM"));
				FileName.TruncateBeforeFirst(AString(ExePath));
				WriteFiles.Add(hFile, FileName);
				if(FS)
					FS->UpdateStdFileIndex(FileName, GetFileSize(hFile, NULL));
			}
		}
	}
	return hFile;
}

BOOL WINAPI MyWriteFile(HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPDWORD lpNumberOfBytesWritten, LPOVERLAPPED lpOverlapped)
{
	BOOL Res = WriteFile(hFile, lpBuffer, nNumberOfBytesToWrite, lpNumberOfBytesWritten, lpOverlapped);
	if(Res && WriteFiles.TagExist(hFile))
	{
		if(FS)
			FS->UpdateStdFileIndex(WriteFiles.GetElement(hFile), GetFileSize(hFile, NULL));
	}
	return Res;
}

BOOL WINAPI MyCloseHandle(HANDLE hObject)
{
	WriteFiles.EraseByTag(hObject);
	return CloseHandle(hObject);
}

bool InstallFsHook(Vdfs& vdfs)
{
	FS = &vdfs;

	// Remove bad files

	bool ChangeWorkDir = false;
	TString WorkPath;
	if(PlatformGetWorkPath(WorkPath) && WorkPath.TruncateBeforeLast(_T("\\")) && WorkPath.Compare(_T("System"), true))
		ChangeWorkDir = (SetCurrentDirectory(_T("..\\")) == TRUE);

	if(PathFileExists(_T("_WORK\\DATA\\TEXTURES\\_COMPILED\\FONT_15_WHITE.FNT")))
	{
		if(GetFileCrc(_T("_WORK\\DATA\\TEXTURES\\_COMPILED\\FONT_15_WHITE.FNT")) == 0xC61A14B6)
			DeleteFile(_T("_WORK\\DATA\\TEXTURES\\_COMPILED\\FONT_15_WHITE.FNT"));
	}

	if(ChangeWorkDir)
		SetCurrentDirectory(_T("System\\"));

	// Install hooks for vdfs index update

	uChar* codeBase = (uChar*)GetModuleHandle(NULL);
	PIMAGE_IMPORT_DESCRIPTOR importDesc = GetImportDescriptor(codeBase, "KERNEL32.dll");
	if(importDesc)
	{
		PatchImportFunctionAddress<FARPROC>(codeBase, importDesc, false, "CreateFileA", (FARPROC)MyCreateFileA);
		PatchImportFunctionAddress<FARPROC>(codeBase, importDesc, false, "WriteFile", (FARPROC)MyWriteFile);
		PatchImportFunctionAddress<FARPROC>(codeBase, importDesc, false, "CloseHandle", (FARPROC)MyCloseHandle);
	}

	return true;
}