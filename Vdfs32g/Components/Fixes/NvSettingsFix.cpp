#include "PreCompiled.h"

#include "Common/TextLogger.h"

#include <nvapi.h>
#include <NvApiDriverSettings.h>
#include <string>

#pragma comment (lib, "nvapi.lib")

class NvidiaApi
{
public:
	NvAPI_Status status;

	NvidiaApi()
	{
		status = NvAPI_Initialize();
		Log("NvAPI_Initialize", status);
	}

	void Log(std::string action, _NvAPI_Status status)
	{
		TextLogger::Log() << action << ": ";
		NvAPI_ShortString desc;
		NvAPI_GetErrorMessage(status, desc);
		TextLogger::Log(desc);
	}

	bool IsOk()
	{
		return status == NVAPI_OK;
	}

	void SetRefreshRateOverride(std::string deviceName, float value)
	{
		if (!IsOk())
		{
			return;
		}

		Log(deviceName, status);

		NvUnAttachedDisplayHandle uHandle;
		status = NvAPI_DISP_GetAssociatedUnAttachedNvidiaDisplayHandle(deviceName.c_str(), &uHandle);
		Log("NvAPI_DISP_GetAssociatedUnAttachedNvidiaDisplayHandle", status);
		
		if (status != NVAPI_OK && status != NVAPI_NVIDIA_DEVICE_NOT_FOUND)
		{
			return;
		}

		NvDisplayHandle aHandle;
	
		if (status != NVAPI_NVIDIA_DEVICE_NOT_FOUND)
		{
			status = NvAPI_CreateDisplayFromUnAttachedDisplay(uHandle, &aHandle);
			Log("NvAPI_CreateDisplayFromUnAttachedDisplay", status);
		}
		else
		{
			status = NvAPI_GetAssociatedNvidiaDisplayHandle(deviceName.c_str(), &aHandle);
			Log("NvAPI_GetAssociatedNvidiaDisplayHandle", status);
		}
			
		if (!IsOk())
		{
			return;
		}

		NvAPI_SetRefreshRateOverride(aHandle, 0x00000000, value, 0);
		Log("NvAPI_SetRefreshRateOverride", status);
	}

	void SetRefreshRateSetting()
	{
		if (!IsOk())
		{
			return;
		}

		WCHAR charBuffer[2048];
		GetModuleFileNameW(NULL, charBuffer, 2048);
		TextLogger::Log((std::wstring)charBuffer);

		NvDRSSessionHandle session;
		
		status = NvAPI_DRS_CreateSession(&session);
		Log("NvAPI_DRS_CreateSession", status);

		status = NvAPI_DRS_LoadSettings(session);
		Log("NvAPI_DRS_LoadSettings", status);

		const wchar_t* profiles[2] =
		{
			L"Gothic 1",
			L"Gothic 2"
		};

		for (int i = 0; i < 2; i++)
		{
			NvDRSProfileHandle profile;
			NvAPI_DRS_FindProfileByName(session, (NvU16*)profiles[i], &profile);
			Log("NvAPI_DRS_FindProfileByName", status);
			
			NVDRS_SETTING drsSetting;
			drsSetting.version = NVDRS_SETTING_VER;
			drsSetting.settingId = REFRESH_RATE_OVERRIDE_ID;
			drsSetting.settingType = NVDRS_DWORD_TYPE;
			drsSetting.u32CurrentValue = REFRESH_RATE_OVERRIDE_APPLICATION_CONTROLLED;
			status = NvAPI_DRS_SetSetting(session, profile, &drsSetting);
			Log("NvAPI_DRS_SetSetting (REFRESH_RATE_OVERRIDE_ID)", status);
		}

		status = NvAPI_DRS_SaveSettings(session);
		Log("NvAPI_DRS_SaveSettings", status);

		status = NvAPI_DRS_DestroySession(session);
		Log("NvAPI_DRS_DestroySession", status);
	}

	~NvidiaApi()
	{
		status = NvAPI_Unload();
		Log("NvAPI_Unload", status);
	}
};

extern "C"
{
	bool InstallNvSettingsFix()
	{
		char NvSettingsFix[256];
		if(!GothicReadIniString("DEBUG", "NvSettingsFix", "1", NvSettingsFix, 256, "SystemPack.ini"))
			GothicWriteIniString("DEBUG", "NvSettingsFix", "1", "SystemPack.ini");

		if(atoi(NvSettingsFix) == 1)
		{
			TextLogger::Log("NvSettingsFix just started");
			NvidiaApi nvApi;
			nvApi.SetRefreshRateSetting();
			TextLogger::Log() << std::endl;
		}
		return true;
	}
}