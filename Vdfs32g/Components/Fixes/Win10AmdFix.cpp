#include "PreCompiled.h"

#include <d3d9.h>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

#include "Common/TextLogger.h"

using namespace std;

typedef LONG NTSTATUS, *PNTSTATUS;
#define STATUS_SUCCESS (0x00000000)

typedef NTSTATUS (WINAPI* RtlGetVersionPtr)(PRTL_OSVERSIONINFOW);

extern "C"
{
	RTL_OSVERSIONINFOW GetRealOSVersion(void)
	{
		HMODULE hMod = ::GetModuleHandleW(L"ntdll.dll");

		if (hMod)
		{
			RtlGetVersionPtr fxPtr = (RtlGetVersionPtr)::GetProcAddress(hMod, "RtlGetVersion");

			if (fxPtr) 
			{
				RTL_OSVERSIONINFOW rovi = { 0 };
				rovi.dwOSVersionInfoSize = sizeof(rovi);
				if (STATUS_SUCCESS == fxPtr(&rovi))
					return rovi;
			}
		}

		RTL_OSVERSIONINFOW rovi = { 0 };
		return rovi;
	}
}

const int AMD_VEN = 0x1002;
const int NVIDIA_VEN = 0x10DE;
const string AMD_PREFIX    = "PCI\\VEN_1002&";
const string NVIDIA_PREFIX = "PCI\\VEN_10DE&";

struct Display 
{
	string Name;
	string VideoDevice;
	bool   Primary;
	bool   IsActive;
	bool   IsAMD;
	bool   IsNVIDIA;
	unsigned long Id;

	Display(DISPLAY_DEVICEA& device):
		Id(0xFFFFFFFF)
	{
		Name        = device.DeviceName;
		VideoDevice = device.DeviceString;
		Primary     = (device.StateFlags & DISPLAY_DEVICE_PRIMARY_DEVICE) == DISPLAY_DEVICE_PRIMARY_DEVICE;
		IsActive    = (device.StateFlags & DISPLAY_DEVICE_ACTIVE) == DISPLAY_DEVICE_ACTIVE;

		string ID = device.DeviceID;
		IsAMD    = ID.substr( 0, AMD_PREFIX.length()    ).compare( AMD_PREFIX    ) == 0;
		IsNVIDIA = ID.substr( 0, NVIDIA_PREFIX.length() ).compare( NVIDIA_PREFIX ) == 0;
		int pos = ID.find("DEV_", 0);
		
		if (pos < 0)
			return;
		
		istringstream is(ID.substr(pos + 4, 4));
		is >> hex >> Id;
	}
};

struct DisplayInfo
{  
	std::vector<Display*> DisplayList;

	DisplayInfo()
	{
		DISPLAY_DEVICEA dd;
		dd.cb = sizeof( DISPLAY_DEVICEA );
		DWORD deviceNum = 0;

		while( EnumDisplayDevicesA( NULL, deviceNum++, &dd, 0 ) )
			DisplayList.push_back( new Display( dd ) );
	}

	Display* GetPrimaryDevice() {
		for( size_t i = 0; i < DisplayList.size(); i++ )
			if( DisplayList[i]->Primary )
				return DisplayList[i];
		return NULL;
	}

	void CollectAMDDevices( vector<Display*>& collection )
	{
		for( size_t i = 0; i < DisplayList.size(); i++ )
			if( DisplayList[i]->IsAMD )
			collection.push_back( DisplayList[i] );
	}

	Display* GetById(int id) {
		for (size_t i = 0; i < DisplayList.size(); i++)
			if (DisplayList[i]->Id == id)
				return DisplayList[i];
		return NULL;
	}

	~DisplayInfo() 
	{
		for( size_t i = 0; i < DisplayList.size(); i++ )
			delete DisplayList[i];
	}
};

class Direct3D9AdapterInfo
{
private:
	IDirect3D9* device;

public:
	Direct3D9AdapterInfo():
	  device(NULL)
	{
		device = Direct3DCreate9(D3D_SDK_VERSION);
	}

	bool TryGetInfo(D3DADAPTER_IDENTIFIER9& id)
	{
		if (!device)
		{
			return false;
		}

		if (FAILED(device->GetAdapterIdentifier(D3DADAPTER_DEFAULT, 0, &id)))
		{
			return false;
		}

		return true;
	}

	void LogId(const D3DADAPTER_IDENTIFIER9& id)
	{
		TextLogger::Log("Videocard info:");
		ostream& log = TextLogger::Log();
	
		log << "\tDescription: " << id.Description << std::endl;
		log << "\tDeviceId: " << id.DeviceId << std::endl;
		log << "\tDeviceName: " << id.DeviceName << std::endl;
		log << "\tDriver: " << id.Driver << std::endl;
		log << "\tDriverVersion: " << id.DriverVersion.HighPart << "." << id.DriverVersion.LowPart << std::endl;
		log << "\tRevision: " << id.Revision << std::endl;
		log << "\tSubSysId: " << id.SubSysId << std::endl;
		log << "\tVendorId: " << id.VendorId << std::endl;
		log << "\tWHQLLevel: " << id.WHQLLevel << std::endl;
		log << std::endl;
	}

	~Direct3D9AdapterInfo()
	{
		if (device)
		{
			device->Release();
		}
	}
};

int AddOrSetIniInt(const char* filename, const char* section, const char* key, int value)
{
	char ValueRead[256];

	if (!GothicReadIniString(section, key, "0", ValueRead, 256, filename) || atoi(ValueRead) != value)
	{
		char stringValue[256];
		sprintf(stringValue, "%d", value);
		GothicWriteIniString(section, key, stringValue, filename);
	}

	return atoi(ValueRead);
}

int GetIniInt(const char* filename, const char* section, const char* key, const char* value)
{
	char ValueRead[256];
	GothicReadIniString(section, key, value, ValueRead, 256, filename);

	if(!GothicReadIniString(section, key, value, ValueRead, 256, filename))
		GothicWriteIniString(section, key, value, filename);

	return atoi(ValueRead);
}

bool HasAmdVideocardWinApi()
{
	DisplayInfo info;
	vector<Display*> displays;
	info.CollectAMDDevices(displays);
	return displays.size() > 0;
}

bool HasAmdVideocard(Direct3D9AdapterInfo& d3d9api)
{
	D3DADAPTER_IDENTIFIER9 id;

	if (!d3d9api.TryGetInfo(id))
	{
		return HasAmdVideocardWinApi();
	}

	return id.VendorId == AMD_VEN;
}

extern "C"
{
	struct MenuPatchData
	{
		uint32_t textAddress;
		uint32_t dataAddress;

		MenuPatchData(){}

		MenuPatchData(uint32_t textAddress, uint32_t dataAddress):
			textAddress(textAddress),
			dataAddress(dataAddress)
		{
		}

		void Apply(const char* data)
		{
			DWORD old;
			if (!VirtualProtect((void*)textAddress, 4, PAGE_EXECUTE_READWRITE, &old))
			{
				TextLogger::Log("Menu patch failed");
				return;
			}
			
			*(uint32_t*)(void*)textAddress = dataAddress;
			VirtualProtect((void*)textAddress, 4, old, &old);

			strcpy((char*)dataAddress, data);
		}
	};

	// gothic_mod: pa=0x0071F9F3 + 1,
	// gothic_backup: pa=0x0074221D + 3,
	// g1: pa=0x0071F9F3 + 2,
	// g1a: pa=0x0075C23D + 3
	// g2: pa=0x0076B7DD + 2
	// g2a: pa=0x0065830D + 2, da=0x00ABCFE0

	//1C47577B - GothicMod.exe - 1.08k_mod - g1
	//CB86CAC3 - GothicMod.exe - 1.08k_mod + fps патч - g1
	//46E242CB - Gothic2.exe - 1.30(fix) - g2
	//EFD8A07B - Gothic2.exe - 2.6(fix) - g2a
	//F6DD31C4 - Gothic.exe - 1.08k - gothic_backup
	//crc для сиквела
	//C1A66598 - g1a
	//и
	//C2C16E53 - g1a
	void PatchMenu(const char* data)
	{
		map<uint32_t, MenuPatchData> crc2data;

		crc2data[0x1C47577B] = MenuPatchData(0x0071F9F4, 0x009DEF8F);
		crc2data[0xCB86CAC3] = MenuPatchData(0x0071F9F5, 0x009DEF8F);
		crc2data[0x46E242CB] = MenuPatchData(0x0076B7DF, 0x00A88DDD);
		crc2data[0xEFD8A07B] = MenuPatchData(0x0065830F, 0x00ABCFE0);
		crc2data[0xF6DD31C4] = MenuPatchData(0x00742220, 0x00A06E30);
		crc2data[0xC1A66598] = MenuPatchData(0x0075C240, 0x00A28CBF);
		crc2data[0xC2C16E53] = MenuPatchData(0x0075C240, 0x00A28CBF);

		uLong CodeCRC = GetSectionCrc32(".text");
		TextLogger::Log() << "CRC: " << hex << CodeCRC << std::endl;

		map<uint32_t, MenuPatchData>::iterator it = crc2data.find(CodeCRC);

		if (it == crc2data.end())
		{
			return;
		}

		it->second.Apply(data);
	}

	bool InstallWin10AmdFix(void)
	{
		TextLogger::Log("Win10AmdFix just started");

		Direct3D9AdapterInfo d3d9api;
		D3DADAPTER_IDENTIFIER9 id;
		
		if (d3d9api.TryGetInfo(id))
		{
			d3d9api.LogId(id);
			TextLogger::Log("Videocard menu patch just started");
			PatchMenu(id.Description);
			TextLogger::Log("Videocard menu patch just finished");
		}
		else
		{
			TextLogger::Log("DirectX 9 failed: adapter identification");
		}

		if (!GetIniInt("SystemPack.ini", "DEBUG", "Win10AmdFix", "1"))
		{
			return true;
		}

		if (GetRealOSVersion().dwMajorVersion != 10 || !HasAmdVideocard(d3d9api))
		{
			return true;
		}

		AddOrSetIniInt("SystemPack.ini", "DEBUG", "Win10AmdFix", 0);
		AddOrSetIniInt("SystemPack.ini", "DEBUG", "SimpleWindow", 1);
		AddOrSetIniInt("SystemPack.ini", "DEBUG", "BorderlessWindow", 0);
		AddOrSetIniInt("SystemPack.ini", "DEBUG", "FixAppCompat", 0);

		TextLogger::Log("Win10AmdFix was applied");
		return true;
	}
}