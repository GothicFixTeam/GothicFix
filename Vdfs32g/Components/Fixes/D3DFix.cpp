#include "PreCompiled.h"
#include <VersionHelpers.h>

bool PatchD3D(uChar* codeBase)
{
	uInt Signature = 0x88760064;
	unsigned char SubSignature[] = { 0xB8, 0x00, 0x08, 0x00, 0x00, 0x39 };
	unsigned char SubSignatureNew[] = { 0xB8, 0x00, 0x80, 0x00, 0x00, 0x39 };

	DWORD codeSize = GetImportSize(codeBase);
	if(codeSize > sizeof(Signature) + sizeof(SubSignature))
	{
		for(size_t i = 0; i < (codeSize - sizeof(Signature) - sizeof(SubSignature)); i++)
		{
			if(!memcmp(&codeBase[i], &Signature, sizeof(Signature)))
			{
				size_t ToCheck = MIN(64, codeSize - i - sizeof(SubSignature));
				for(size_t n = i; (n - i) < ToCheck; n++)
				{
					if(!memcmp(&codeBase[n], SubSignature, sizeof(SubSignature)))
					{
						DWORD OldProtect = 0;
						if(!VirtualProtect(&codeBase[n], sizeof(SubSignature), PAGE_READWRITE, &OldProtect))
							return false;
						memcpy(&codeBase[n], SubSignatureNew, sizeof(SubSignature));
						VirtualProtect(&codeBase[n], sizeof(SubSignature), OldProtect, &OldProtect);
						i = n + sizeof(SubSignature);
						break;
					}
				}
			}
		}
	}
	return true;
}

static HMODULE hD3Dim = NULL;
typedef int (__stdcall* SetAppCompatDataFunc)(int a1, int a2);

HWND WINAPI MyCreateWindowExA(__in DWORD dwExStyle, __in_opt LPCSTR lpClassName, __in_opt LPCSTR lpWindowName, __in DWORD dwStyle, __in int X, __in int Y, __in int nWidth, __in int nHeight, __in_opt HWND hWndParent, __in_opt HMENU hMenu, __in_opt HINSTANCE hInstance, __in_opt LPVOID lpParam)
{
	if(!strcmp(lpClassName, "DDWndClass"))
	{
		if(!atoi(zStartupWindowed))
		{
			dwExStyle = 0;
			dwStyle = WS_POPUP;
		}
	}
	return CreateWindowExA(dwExStyle, lpClassName, lpWindowName, dwStyle, X, Y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
}

bool InstallD3DFix(void)
{
	char FixHighRes[256];
	if(!GothicReadIniString("DEBUG", "FixHighRes", "1", FixHighRes, 256, "SystemPack.ini"))
		GothicWriteIniString("DEBUG", "FixHighRes", "1", "SystemPack.ini");

	char FixAppCompat[256];
	if(!GothicReadIniString("DEBUG", "FixAppCompat", "1", FixAppCompat, 256, "SystemPack.ini"))
		GothicWriteIniString("DEBUG", "FixAppCompat", "1", "SystemPack.ini");

	HMODULE hDDraw = GetModuleHandle(_T("ddraw.dll"));
	if(hDDraw)
	{
		if(IsWindowsXPOrGreater() && (atoi(FixHighRes) == 1))
		{
			DeleteFile(_T("D3DIM700.dll"));
			if(hD3Dim = LoadLibrary(_T("D3DIM700.dll")))
				PatchD3D((uChar*)hD3Dim);
		}

		if(IsWindows8OrGreater())
		{
			int AppCompatFix = atoi(FixAppCompat);
			switch(AppCompatFix)
			{
			case 1:
				{
					SetAppCompatDataFunc SetAppCompatData = (SetAppCompatDataFunc)GetProcAddress(hDDraw, "SetAppCompatData"); // DXPrimaryEmulation -DisableMaxWindowedMode
					if(SetAppCompatData)
						SetAppCompatData(12, 0);
				}
				break;
			case 2:
				{
					uChar* codeBase = (uChar*)GetModuleHandle(NULL);
					PIMAGE_IMPORT_DESCRIPTOR importDesc = GetImportDescriptor(codeBase, "USER32.dll");
					if(importDesc)
						PatchImportFunctionAddress<FARPROC>(codeBase, importDesc, false, "CreateWindowExA", (FARPROC)MyCreateWindowExA);
				}
				break;
			}
		}
	}
	return true;
}

void RemoveD3DFix(void)
{
	if(hD3Dim)
	{
		FreeLibrary(hD3Dim);
		hD3Dim = NULL;
	}
}