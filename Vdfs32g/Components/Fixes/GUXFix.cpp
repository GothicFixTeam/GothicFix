#include "PreCompiled.h"
#include <VersionHelpers.h>

bool PatchGUX(uChar* codeBase)
{
	unsigned char Signature[] = { 0x68, 0x28, 0x09, 0x00, 0x00 };
	unsigned char SignatureNew[] = { 0xC2, 0x04, 0x00, 0x90, 0x90 };

	DWORD codeSize = GetImportSize(codeBase);
	if(codeSize > sizeof(Signature))
	{
		for(size_t i = 0; i < (codeSize - sizeof(Signature)); i++)
		{
			if(!memcmp(&codeBase[i], &Signature, sizeof(Signature)))
			{
				DWORD OldProtect = 0;
				if(!VirtualProtect(&codeBase[i], sizeof(Signature), PAGE_READWRITE, &OldProtect))
					return false;
				memcpy(&codeBase[i], SignatureNew, sizeof(Signature));
				VirtualProtect(&codeBase[i], sizeof(Signature), OldProtect, &OldProtect);
				i += sizeof(Signature);
				return true;
			}
		}
	}
	return false;
}

bool InstallGUXFix(void)
{	
	char FixGameUX[256];
	if(!GothicReadIniString("DEBUG", "FixGameUX", "1", FixGameUX, 256, "SystemPack.ini"))
		GothicWriteIniString("DEBUG", "FixGameUX", "1", "SystemPack.ini");

	if(IsWindowsVistaOrGreater() && !IsWindows8OrGreater() && (atoi(FixGameUX) == 1))
	{
		HMODULE hGUX = GetModuleHandle(_T("AcGenral.dll"));
		if(hGUX)
			PatchGUX((uChar*)hGUX);
	}

	return true;
}

void RemoveGUXFix(void)
{
}