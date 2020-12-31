#include "PreCompiled.h"
#include "Common/ComPtr.h"
#include <wincodec.h>

HRESULT InitCom(void)
{
	// Due too lack of functionality in other modes (~ no DragDrop support)
	// try OleInitialize first

	HRESULT hRes = S_OK;
	if (SUCCEEDED(hRes = OleInitialize(NULL)))
		return hRes;
	else
		if (hRes == RPC_E_CHANGED_MODE)
		{
			if (SUCCEEDED(hRes = CoInitialize(NULL)))
				return hRes;
			else
				if (hRes == RPC_E_CHANGED_MODE)
				{
					if (SUCCEEDED(hRes = CoInitializeEx(NULL, COINIT_MULTITHREADED)))
						return hRes;
				}
		}
	return hRes;
}

struct BinkFix
{
BINK*		Bink;
uInt		SrcWidth;
uInt		SrcHeight;

uInt		DstWidth;
uInt		DstHeight;

ComPtr<IWICBitmap> Image;
uInt		SrcX;
uInt		SrcY;

ComPtr<IWICBitmapScaler> pIScaler;
};

HRESULT hRes;
ComPtr<IWICImagingFactory> pImgFac;
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

	if (Fix.Image)
	{
		UINT width, height;
		hRes = Fix.Image->GetSize(&width, &height);
		if ((width != ImgWidth) || (height != ImgHeight))
		{
			Fix.Image = nullptr;
		}
	}
	if(!Fix.Image)
	{
		if (FAILED(hRes = pImgFac->CreateBitmap(ImgWidth, ImgHeight, GUID_WICPixelFormat32bppBGR, WICBitmapCacheOnDemand, Fix.Image.GetAddressOf())))
		{
			Fix.Image = nullptr;
		}
		if (FAILED(hRes = pImgFac->CreateBitmapScaler(Fix.pIScaler.GetAddressOf())))
		{
			Fix.pIScaler = nullptr;
		}
		if (FAILED(hRes = Fix.pIScaler->Initialize(Fix.Image, Fix.DstWidth, Fix.DstHeight, WICBitmapInterpolationModeFant)))
		{
			Fix.pIScaler = nullptr;
		}
	}
}

void CreateBinkFix(BINK* bnk)
{
	char Buffer[256];
	GothicReadIniString("GAME", "scaleVideos", "1", Buffer, 256, "Gothic.ini");
	scaleVideos = atoi(Buffer);

	if(!bnk || !scaleVideos)
		return;

	POINT GothicWindowSize = { 0, 0 };
	if(!GetGothicWindowSize(GothicWindowSize))
		return;

	uInt Index = GetBinkIndex(bnk);
	if(!Index)
	{
		BinkFix& Fix = Binks.Add();

		Fix.Bink = bnk;
		Fix.SrcWidth = bnk->Width;
		Fix.SrcHeight = bnk->Height;
		Fix.DstWidth = GothicWindowSize.x;
		Fix.DstHeight = GothicWindowSize.y;

		ValidateAspect(Fix, 0, 0);

		bnk->Width = Fix.DstWidth;
		bnk->Height = Fix.DstHeight;
	}
	return;
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
		int res = 0;
		BinkFix& Fix = Binks[Index - 1];
		if(Fix.Image)
		{
			// Should be in {} for destroying all 'srcLock' related objects before using 'Image'
			{
				UINT width, height;
				hRes = Fix.Image->GetSize(&width, &height);
				WICRect rect{ 0, 0, (INT)width, (INT)height };

				ComPtr<IWICBitmapLock> srcLock;
				hRes = Fix.Image->Lock(&rect, WICBitmapLockWrite, srcLock.GetAddressOf());
				UINT size, stride;
				BYTE* data;
				srcLock->GetDataPointer(&size, &data);
				srcLock->GetStride(&stride);

				bnk->Width = Fix.SrcWidth;
				bnk->Height = Fix.SrcHeight;
				res = dll->BinkCopyToBuffer(bnk, data, stride, height, Fix.SrcX, Fix.SrcY, flags);
				bnk->Width = Fix.DstWidth;
				bnk->Height = Fix.DstHeight;
			}
			if (Fix.pIScaler)
			{
				UINT dstBufferSize = destpitch * destheight;
				hRes = Fix.pIScaler->CopyPixels(nullptr, destpitch, dstBufferSize, (BYTE*)dest);
				return res;
			}
		}
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
	char FixBink[256];
	if (!GothicReadIniString("DEBUG", "FixBink", "1", FixBink, 256, "SystemPack.ini"))
	{
		GothicWriteIniString("DEBUG", "FixBink", "1", "SystemPack.ini");
	}

	if (atoi(FixBink) == 1)
	{
		if (FAILED(hRes = InitCom()))
		{
			return false;
		}
		if (FAILED(hRes = CoCreateInstance(CLSID_WICImagingFactory1, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(pImgFac.GetAddressOf()))))
		{
			return false;
		}

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