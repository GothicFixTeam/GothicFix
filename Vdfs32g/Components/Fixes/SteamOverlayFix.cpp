#include "PreCompiled.h"

static bool	Prepared = false;	
static uChar Bak[5] = {};

bool PrepareSteamOverlayFix(void)
{
	char SteamOverlayFix[256];
	GothicReadIniString("DEBUG", "SteamOverlayFix", "1", SteamOverlayFix, 256, "SystemPack.ini");

	if(atoi(SteamOverlayFix))
	{
		uChar* codeBase = (uChar*)GetModuleHandle(NULL);
		PIMAGE_IMPORT_DESCRIPTOR importDesc = GetImportDescriptor(codeBase, "ddraw.dll");
		if(importDesc)
		{
			FARPROC* Res = GetImportFunctionAddress(codeBase, importDesc, false, "DirectDrawCreateEx");
			if(Res && *Res)
			{
				uChar* Raw = (uChar*)*Res;
				memcpy(Bak, Raw, 5);
				Prepared = true;
			}
		}
	}
	return true;
}

bool InstallSteamOverlayFix(void)
{
	if(Prepared)
	{
		uChar* codeBase = (uChar*)GetModuleHandle(NULL);
		PIMAGE_IMPORT_DESCRIPTOR importDesc = GetImportDescriptor(codeBase, "ddraw.dll");
		if(importDesc)
		{
			FARPROC* Res = GetImportFunctionAddress(codeBase, importDesc, false, "DirectDrawCreateEx");
			uChar* Raw = (uChar*)*Res;
			for(uInt i = 0; i < 5; i++)
				PatchAddress<uChar>(&Raw[i], Bak[i]);
		}
	}
	return true;
}