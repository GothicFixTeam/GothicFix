#include "PreCompiled.h"

#include <fwImage.h>
#ifdef _DEBUG
#pragma comment(lib, "fwImaged.lib")
#pragma comment(lib, "fwBased.lib")
#else
#pragma comment(lib, "fwImage.lib")
#pragma comment(lib, "fwBase.lib")
#endif

struct BinkFix
{
BINK*		Bink;
uInt		SrcWidth;
uInt		SrcHeight;

uInt		DstWidth;
uInt		DstHeight;

IplImage*	Image;
uInt		SrcX;
uInt		SrcY;

IplImage*	Resized;
};

Array<BinkFix> Binks;

uInt GetBinkIndex(BINK* bnk)
{
	for(uInt i = 0; i < Binks.Size(); i++)
	{
		if(Binks[i].Bink == bnk)
			return (i + 1);
	}
	return 0;
}

BOOL scaleVideos = TRUE;

void ValidateAspect(BinkFix& Fix, uInt destx, uInt desty)
{
	uInt ImgWidth = Fix.SrcWidth;
	uInt ImgHeight = Fix.SrcHeight;

	Fix.SrcX = 0;
	Fix.SrcY = 0;

	float SrcAspect = (float)Fix.SrcWidth / (float)Fix.SrcHeight;
	float DstAspect = (float)Fix.DstWidth / (float)Fix.DstHeight;
	if(DstAspect < SrcAspect)
	{
		ImgHeight = (uInt)((float)Fix.SrcWidth / DstAspect);
		ImgHeight -= ImgHeight % 2;
		Fix.SrcY += (ImgHeight - Fix.SrcHeight) / 2;
	}
	else
	if(DstAspect > SrcAspect)
	{
		ImgWidth = (int)((float)Fix.SrcHeight * DstAspect);
		ImgWidth -= ImgWidth % 2;
		Fix.SrcX += (ImgWidth - Fix.SrcWidth) / 2;
	}

	if(Fix.Image && ((Fix.Image->width != ImgWidth) || (Fix.Image->height != ImgHeight)))
		cvReleaseImage(&Fix.Image);

	if(!Fix.Image)
	{
		Fix.Image = cvCreateImage(cvSize(ImgWidth, ImgHeight), IPL_DEPTH_8U, 4);
		cvSet(Fix.Image, cvScalar(0));
	}
}

bool CreateBinkFix(BINK* bnk)
{
	char Buffer[256];
	GothicReadIniString("GAME", "scaleVideos", "1", Buffer, 256, "Gothic.ini");
	scaleVideos = atoi(Buffer);

	if(!bnk || !scaleVideos)
		return false;

	POINT GothicWindowSize = { 0, 0 };
	if(!GetGothicWindowSize(GothicWindowSize))
		return false;

	uInt Index = GetBinkIndex(bnk);
	if(!Index)
	{
		BinkFix& Fix = Binks.Add();
		Fix.Image = Fix.Resized = NULL;

		Fix.Bink = bnk;
		Fix.SrcWidth = bnk->Width;
		Fix.SrcHeight = bnk->Height;
		Fix.DstWidth = GothicWindowSize.x;
		Fix.DstHeight = GothicWindowSize.y;

		ValidateAspect(Fix, 0, 0);

		bnk->Width = Fix.DstWidth;
		bnk->Height = Fix.DstHeight;
	}
	return true;
}

bool ApplyBinkFix(BINK* bnk)
{
	if(!bnk || !scaleVideos)
		return false;

	uInt Index = GetBinkIndex(bnk);
	if(Index)
	{
		BinkFix& Fix = Binks[Index - 1];
		bnk->Width = Fix.DstWidth;
		bnk->Height = Fix.DstHeight;
		return true;
	}
	return false;
}

int BinkFixBinkCopyToBuffer(cBinkDll* dll, BINK* bnk, void* dest, int destpitch, uInt destheight, uInt destx, uInt desty, uInt flags)
{
	if(!bnk || !(flags & BINK_SURFACE_32) || !scaleVideos)
		return dll->BinkCopyToBuffer(bnk, dest, destpitch, destheight, destx, desty, flags);

	uInt Index = GetBinkIndex(bnk);
	if(Index)
	{
		BinkFix& Fix = Binks[Index - 1];

		//Fix.DstWidth = destpitch / 4;
		//Fix.DstHeight = destheight;
		//ValidateAspect(Fix, destx, desty);

		bnk->Width = Fix.SrcWidth;
		bnk->Height = Fix.SrcHeight;

		int res = dll->BinkCopyToBuffer(bnk, Fix.Image->imageData, Fix.Image->widthStep, Fix.Image->height, Fix.SrcX, Fix.SrcY, flags);

		bnk->Width = Fix.DstWidth;
		bnk->Height = Fix.DstHeight;

		if(Fix.Resized && ((Fix.Resized->width != destpitch / 4) || (Fix.Resized->height != destheight)))
			cvReleaseImageHeader(&Fix.Resized);
		if(!Fix.Resized)
			Fix.Resized = cvCreateImageHeader(cvSize(destpitch / 4, destheight), Fix.Image->depth, Fix.Image->nChannels);
		Fix.Resized->imageData = (char*)dest;

		if((Fix.Resized->width != Fix.DstWidth) || (Fix.Resized->height != Fix.DstHeight))
			cvSetImageROI(Fix.Resized, cvRect(0, 0, Fix.DstWidth, Fix.DstHeight));

		FwiSize fwSrcSize;
		fwSrcSize.width = Fix.Image->width;
		fwSrcSize.height = Fix.Image->height;

		FwiRect fwSrcRoi;
		fwSrcRoi.x = 0;
		fwSrcRoi.y = 0;
		fwSrcRoi.width = fwSrcSize.width;
		fwSrcRoi.height = fwSrcSize.height;

		FwiSize fwDstRoi;
		fwDstRoi.width = Fix.DstWidth;
		fwDstRoi.height = Fix.DstHeight;

		float xFactor = (float)Fix.DstWidth / (float)Fix.Image->width;
		float yFactor = (float)Fix.DstHeight / (float)Fix.Image->height;

		//Timer Measure;
		//Measure.Start();
		fwiResize_8u_C4R((Fw8u*)Fix.Image->imageData, fwSrcSize, Fix.Image->widthStep, fwSrcRoi, (Fw8u*)Fix.Resized->imageData, Fix.Resized->widthStep, fwDstRoi, xFactor, yFactor, FWI_INTER_LINEAR);
		//cvResize(Fix.Image, Fix.Resized, CV_INTER_LINEAR);
		//printf("%f\n", Measure.GetElapsedTimeSeconds());

		return res;
	}

	return dll->BinkCopyToBuffer(bnk, dest, destpitch, destheight, destx, desty, flags);
}

bool CancelBinkFix(BINK* bnk)
{
	if(!bnk || !scaleVideos)
		return false;

	uInt Index = GetBinkIndex(bnk);
	if(Index)
	{
		BinkFix& Fix = Binks[Index - 1];
		bnk->Width = Fix.SrcWidth;
		bnk->Height = Fix.SrcHeight;
		return true;
	}
	return false;
}

bool DeleteBinkFix(BINK* bnk)
{
	if(!bnk || !scaleVideos)
		return false;

	uInt Index = GetBinkIndex(bnk);
	if(Index)
	{
		BinkFix& Fix = Binks[Index - 1];
		bnk->Width = Fix.SrcWidth;
		bnk->Height = Fix.SrcHeight;
		cvReleaseImage(&Fix.Image);
		if(Fix.Resized)
			cvReleaseImageHeader(&Fix.Resized);
		Binks.EraseIndex(Index - 1);
		return true;
	}
	return false;
}

// Overrides

cBinkDll* OrgDll = NULL;

int __stdcall BinkSetSoundOnOff(BINK* bnk, int onoff)
{
	if(OrgDll)
	{
		CancelBinkFix(bnk);
		int res = OrgDll->BinkSetSoundOnOff(bnk, onoff);
		ApplyBinkFix(bnk);
		return res;
	}
	return 0;
}

// Common && Video

void __stdcall BinkNextFrame(BINK* bnk)
{
	if(OrgDll)
	{
		CancelBinkFix(bnk);
		OrgDll->BinkNextFrame(bnk);
		ApplyBinkFix(bnk);
	}
}

void __stdcall BinkGoto(BINK* bnk,uInt frame,int flags)
{
	if(OrgDll)
	{
		CancelBinkFix(bnk);
		OrgDll->BinkGoto(bnk, frame, flags);
		ApplyBinkFix(bnk);
	}
}

int __stdcall BinkWait(BINK* bnk)
{
	if(OrgDll)
	{
		CancelBinkFix(bnk);
		int res = OrgDll->BinkWait(bnk);
		ApplyBinkFix(bnk);
		return res;
	}
	return 0;
}

int __stdcall BinkCopyToBuffer(BINK* bnk, void* dest, int destpitch, uInt destheight, uInt destx, uInt desty, uInt flags)
{
	if(OrgDll)
		return BinkFixBinkCopyToBuffer(OrgDll, bnk, dest, destpitch, destheight, destx, desty, flags);
	return 0;
}

int __stdcall BinkDoFrame(BINK* bnk)
{
	if(OrgDll)
	{
		CancelBinkFix(bnk);
		int res = OrgDll->BinkDoFrame(bnk);
		ApplyBinkFix(bnk);
		return res;
	}
	return 0;
}

BINK* __stdcall BinkOpen(const char* name, uInt flags)
{
	if(OrgDll)
	{
		// if resolution is higher than game window size video will be skipped, 
		// so we tell Gothic video have correct resolution and scale video internally
		BINK* res = OrgDll->BinkOpen(name, flags);
		CreateBinkFix(res);
		return res;
	}
	return NULL;
}

void __stdcall BinkClose(BINK* bnk)
{
	if(OrgDll)
	{
		DeleteBinkFix(bnk);
		OrgDll->BinkClose(bnk);
	}
}

void __stdcall BinkSetVolumeG2(BINK* bnk, uInt trackid, int volume)
{
	if(OrgDll)
	{
		CancelBinkFix(bnk);
		if(OrgDll->BinkSetVolumeG2)
			OrgDll->BinkSetVolumeG2(bnk, trackid, volume);
		else
			OrgDll->BinkSetVolumeG1(bnk, volume);
		ApplyBinkFix(bnk);
	}
}

void __stdcall BinkSetVolumeG1(BINK* bnk, int volume)
{
	if(OrgDll)
	{
		CancelBinkFix(bnk);
		if(OrgDll->BinkSetVolumeG1)
			OrgDll->BinkSetVolumeG1(bnk, volume);
		else
			OrgDll->BinkSetVolumeG2(bnk, 0, volume);
		ApplyBinkFix(bnk);
	}
}

int __stdcall BinkPause(BINK* bnk,int pause)
{
	if(OrgDll)
	{
		CancelBinkFix(bnk);
		int res = OrgDll->BinkPause(bnk, pause);
		ApplyBinkFix(bnk);
		return res;
	}
	return 0;
}

#include <intrin.h>

bool InstallBinkFix(void)
{
	int cpuInfo[4];
	__cpuid(cpuInfo, 1);
	if(((cpuInfo[3] & ((int)1 << 25)) != 0) && ((cpuInfo[3] & ((int)1 << 26)) != 0))
	{
		char FixBink[256];
		if(!GothicReadIniString("DEBUG", "FixBink", "1", FixBink, 256, "SystemPack.ini"))
			GothicWriteIniString("DEBUG", "FixBink", "1", "SystemPack.ini");

		if(atoi(FixBink) == 1)
		{
			uChar* codeBase = (uChar*)GetModuleHandle(NULL);
			PIMAGE_IMPORT_DESCRIPTOR importDesc = GetImportDescriptor(codeBase, "binkw32.dll");
			if(importDesc)
			{
				OrgDll = new cBinkDll(_T("BinkW32.dll"));
				if(!OrgDll->Load())
				{
					MessageBox(NULL, _T("Invalid binkw32.dll"), _T("Error"), MB_ICONERROR);
					delete OrgDll;
					OrgDll = NULL;
					return false;
				}

				bool Ok = true;
				Ok = Ok && PatchImportFunctionAddress<FARPROC>(codeBase, importDesc, false, "_BinkSetSoundOnOff@8", (FARPROC)BinkSetSoundOnOff);
				Ok = Ok && PatchImportFunctionAddress<FARPROC>(codeBase, importDesc, false, "_BinkClose@4", (FARPROC)BinkClose);
				Ok = Ok && PatchImportFunctionAddress<FARPROC>(codeBase, importDesc, false, "_BinkNextFrame@4", (FARPROC)BinkNextFrame);
				Ok = Ok && PatchImportFunctionAddress<FARPROC>(codeBase, importDesc, false, "_BinkGoto@12", (FARPROC)BinkGoto);
				Ok = Ok && PatchImportFunctionAddress<FARPROC>(codeBase, importDesc, false, "_BinkWait@4", (FARPROC)BinkWait);
				Ok = Ok && PatchImportFunctionAddress<FARPROC>(codeBase, importDesc, false, "_BinkCopyToBuffer@28", (FARPROC)BinkCopyToBuffer);
				Ok = Ok && PatchImportFunctionAddress<FARPROC>(codeBase, importDesc, false, "_BinkDoFrame@4", (FARPROC)BinkDoFrame);
				Ok = Ok && PatchImportFunctionAddress<FARPROC>(codeBase, importDesc, false, "_BinkOpen@8", (FARPROC)BinkOpen);
				Ok = Ok && (PatchImportFunctionAddress<FARPROC>(codeBase, importDesc, false, "_BinkSetVolume@12", (FARPROC)BinkSetVolumeG2) ||
							PatchImportFunctionAddress<FARPROC>(codeBase, importDesc, false, "_BinkSetVolume@8", (FARPROC)BinkSetVolumeG1));
				Ok = Ok && PatchImportFunctionAddress<FARPROC>(codeBase, importDesc, false, "_BinkPause@8", (FARPROC)BinkPause);
				return Ok;
			}
		}
	}
	return true;
}

void RemoveBinkFix(void)
{
	if(OrgDll)
	{
		delete OrgDll;
		OrgDll = NULL;
	}
}