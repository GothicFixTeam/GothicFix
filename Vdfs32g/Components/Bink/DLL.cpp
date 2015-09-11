#include "PreCompiled.h"

void* DLL::GetFuncPtr(const char* funcname)
{
	if(hDLL) return (void*)GetProcAddress(hDLL, funcname);
	return NULL;
}

DLL::DLL(const TCHAR* name)
{
	hDLL = LoadLibrary(name);
}

DLL::~DLL(void)
{
	if(hDLL) 
	{
		FreeLibrary(hDLL);
		hDLL = NULL;
	}
}

cBinkDll::cBinkDll(const TCHAR* name) : DLL(name)
{
	BinkOpen = NULL;
	BinkGoto = NULL;
	BinkSetSoundOnOff = NULL;
	BinkSetVolumeG1 = NULL;
	BinkSetVolumeG2 = NULL;
	BinkClose = NULL;
	BinkWait = NULL;
	BinkDoFrame = NULL;
	BinkNextFrame = NULL;
	BinkPause = NULL;
	BinkCopyToBuffer = NULL;
}

bool cBinkDll::Load(void)
{
	if(!GetFuncPtr(BINK_GET_ERROR_FUNC_NAME))
		return false;
	if(!(BinkOpen = (BinkOpenFuncPtr)GetFuncPtr(BINK_OPEN_FUNC_NAME)))
	{
		return false;
	}
	if(!(BinkGoto = (BinkGotoFuncPtr)GetFuncPtr(BINK_GOTO_FUNC_NAME)))
	{
		return false;
	}
	if(!(BinkSetSoundOnOff = (BinkSetSoundOnOffFuncPtr)GetFuncPtr(BINK_SET_SOUND_ON_OFF_FUNC_NAME)))
	{
		return false;
	}
	if(!(BinkSetVolumeG1 = (BinkSetVolumeFuncG1Ptr)GetFuncPtr(BINK_SET_VOLUME_G1_FUNC_NAME)) && 
		!(BinkSetVolumeG2 = (BinkSetVolumeFuncG2Ptr)GetFuncPtr(BINK_SET_VOLUME_G2_FUNC_NAME)))
	{
		return false;
	}
	if(!(BinkClose = (BinkCloseFuncPtr)GetFuncPtr(BINK_CLOSE_FUNC_NAME)))
	{
		return false;
	}
	if(!(BinkWait = (BinkWaitFuncPtr)GetFuncPtr(BINK_WAIT_FUNC_NAME)))
	{
		return false;
	}
	if(!(BinkDoFrame = (BinkDoFrameFuncPtr)GetFuncPtr(BINK_DO_FRAME_FUNC_NAME)))
	{
		return false;
	}
	if(!(BinkNextFrame = (BinkNextFrameFuncPtr)GetFuncPtr(BINK_NEXT_FRAME_FUNC_NAME)))
	{
		return false;
	}
	if(!(BinkPause = (BinkPauseFuncPtr)GetFuncPtr(BINK_PAUSE_FUNC_NAME)))
	{
		return false;
	}
	if(!(BinkCopyToBuffer = (BinkCopyToBufferFuncPtr)GetFuncPtr(BINK_COPY_TO_BUFFER_FUNC_NAME)))
	{
		return false;
	}
	return true;
}