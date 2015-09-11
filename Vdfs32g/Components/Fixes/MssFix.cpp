#include "PreCompiled.h"

#include "mssds3d_m3d.h"
#include "mssds3dh_m3d.h"

bool ExtractLibG2(TString& name)
{
	bool Result = false;
	if(PlatformGetTempPath(name))
	{
		name += _T(MSSDS3D_M3D);
		FILE* temp = _tfopen(name, _T("wb"));
		if(temp)
		{
			fwrite(mssds3d_m3d, 1, sizeof(mssds3d_m3d), temp);
			Result = true;
			fclose(temp);
		}
	}
	return Result;
}

bool ExtractLibG1(TString& name)
{
	bool Result = false;
	if(PlatformGetTempPath(name))
	{
		name += _T(MSSDS3DH_M3D);
		FILE* temp = _tfopen(name, _T("wb"));
		if(temp)
		{
			fwrite(mssds3dh_m3d, 1, sizeof(mssds3dh_m3d), temp);
			Result = true;
			fclose(temp);
		}
	}
	return Result;
}

HMODULE WINAPI MyLoadLibraryA(LPCSTR lpLibFileName)
{
	const char* file = strrchr(lpLibFileName, '\\');
	if(file)
	{
		if(!_stricmp(file + 1, "mssds3d.m3d"))
		{
			TString LibName;
			if(ExtractLibG2(LibName))
				return LoadLibrary(LibName);
		}
		else
		if(!_stricmp(file + 1, "mssds3dh.m3d"))
		{
			TString LibName;
			if(ExtractLibG1(LibName))
				return LoadLibrary(LibName);
		}
	}
	return LoadLibraryA(lpLibFileName);
}

bool InstallMssFix(void)
{
	char FixMss[256];
	if(!GothicReadIniString("DEBUG", "FixMss", "1", FixMss, 256, "SystemPack.ini"))
		GothicWriteIniString("DEBUG", "FixMss", "1", "SystemPack.ini");

	if(IsWindowsVistaOrGreater() && (atoi(FixMss) == 1))
	{
		uChar* codeBase = (uChar*)GetModuleHandle(_T("Mss32.dll"));
		if(codeBase)
		{
			PIMAGE_IMPORT_DESCRIPTOR importDesc = GetImportDescriptor(codeBase, "KERNEL32.dll");
			if(!importDesc)
				return false;
			return PatchImportFunctionAddress<FARPROC>(codeBase, importDesc, false, "LoadLibraryA", (FARPROC)MyLoadLibraryA);
		}
	}
	return true;
}

void RemoveMssFix(void)
{
}