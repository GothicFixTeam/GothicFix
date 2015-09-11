#include "PreCompiled.h"

Vdfs	VdfsBase;

long _cdecl vdf_fopen(const char* filename, long flags) 
{
	IfsBase* res = VdfsBase.OpenFile(filename, flags);
	if(res)
		return (int)res;
	VdfsBase.SetLastError(AString(filename) + " file not found");
	return -1;
}

long _cdecl vdf_fclose(long fp) 
{
	VdfsBase.CloseFile((IfsBase*)fp);
	return 0; 
}

long _cdecl vdf_fread(long fp, char* buffer, long size) 
{
	if(fp)
		return ((IfsBase*)fp)->GetData(buffer, size);
	return 0;
}

long _cdecl vdf_fseek(long fp, long offset) 
{
	return (((IfsBase*)fp)->SetOffset(offset) ? offset : -1);
}

long _cdecl vdf_ftell(long fp) 
{
	return ((IfsBase*)fp)->GetOffset(); 
}

long _cdecl vdf_fexists(const char* filename, long flags) 
{
	return VdfsBase.FileExist(filename, flags);
}

long _cdecl vdf_searchfile(const char* filename, char* fullname) 
{
	*fullname = '\0';
	return VdfsBase.SearchFile(filename, fullname) ? 1 : 0;
};

long _cdecl vdf_getlasterror(char* text)
{
	VdfsBase.GetLastError(text);
	return 0;
}

long _cdecl vdf_initall(long numdisks, const char* cdid, long* cddrives, long* disksfound)
{
	InstallSteamOverlayFix();

	if(!IsVdfs())
	{
		if(VdfsBase.Init())
			return 0; // Ok
		return -1; // No files
	}
	return 0;
}

long _cdecl vdf_exitall(void) 
{
	VdfsBase.Clear();
	return 0;
}

long _cdecl vdf_ffilesize(long fp) 
{
	return ((IfsBase*)fp)->GetFileSize(); 
}

// Not implemented
long _cdecl vdf_getdir(char* dirname)
{
	MessageBox(NULL, _T("Unsupported function vdf_getdir"), _T("VDFS"), MB_ICONERROR);
	return -1; 
}

long _cdecl vdf_findopen(const char* path, long flags)
{
	MessageBox(NULL, _T("Unsupported function vdf_findopen"), _T("VDFS"), MB_ICONERROR);
	return NULL; 
}

long _cdecl vdf_findnext(long find, char* filename)
{
	MessageBox(NULL, _T("Unsupported function vdf_findnext"), _T("VDFS"), MB_ICONERROR);
	return -1; 
}

long _cdecl vdf_findclose(long find)
{
	MessageBox(NULL, _T("Unsupported function vdf_findclose"), _T("VDFS"), MB_ICONERROR);
	return -1; 
}

// Internal

long _cdecl vdf_initall_internal(void)
{
	if(VdfsBase.InitVirtual())
		return 0; // Ok
	return -1; // No files
}

// Not used
int _cdecl vdf_fseekrel(void) { return 0; };
int _cdecl vdf_fdirexist(void) { return 0; };
int _cdecl vdf_changedir(void) { return 0; };
int _cdecl GetFileInfo(void) { return 0; };
int _cdecl vdf_setOption(void) { return 0; };
int _cdecl vdf_GetOption(void) { return 0; };

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		{
			bool Ok = true;
			if(!IsVdfs() && !IsSpacer())
			{
				//RedirectIOToConsole();
				Ok = Ok && InstallKillerFix();
				Ok = Ok && InstallGUXFix();
				Ok = Ok && InstallD3DFix();
				Ok = Ok && InstallIniFix();
				Ok = Ok && InstallBinkFix();
				Ok = Ok && InstallSplashFix();
				Ok = Ok && InstallSendMsgFix();
				Ok = Ok && InstallMssFix();
				Ok = Ok && PrepareSteamOverlayFix();
			}
			return Ok ? TRUE : FALSE;
		}
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		{
			if(!IsVdfs() && !IsSpacer())
			{
				RemoveMssFix();
				RemoveSplashFix();
				RemoveSplashFix();
				RemoveBinkFix();
				RemoveIniFix();
				RemoveD3DFix();
				RemoveKillerFix();
			}
		}
		break;
	}
	return TRUE;
}