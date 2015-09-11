#ifndef _DLL_
#define _DLL_

class DLL
{
protected:
	HMODULE			hDLL;

public:
	void* GetFuncPtr(const char* name);
	DLL(const TCHAR* name);
	virtual ~DLL(void);
};

class cBinkDll : public DLL
{
public:
	BinkOpenFuncPtr					BinkOpen;
	BinkGotoFuncPtr					BinkGoto;
	BinkSetSoundOnOffFuncPtr		BinkSetSoundOnOff;
	BinkSetVolumeFuncG1Ptr			BinkSetVolumeG1;
	BinkSetVolumeFuncG2Ptr			BinkSetVolumeG2;
	BinkCloseFuncPtr				BinkClose;
	BinkWaitFuncPtr					BinkWait;
	BinkDoFrameFuncPtr				BinkDoFrame;
	BinkNextFrameFuncPtr			BinkNextFrame;
	BinkPauseFuncPtr				BinkPause;
	BinkCopyToBufferFuncPtr			BinkCopyToBuffer;

public:
	cBinkDll(const TCHAR* data);
	cBinkDll(void);
	bool Load(void);
	virtual ~cBinkDll(void) {};
};

#endif