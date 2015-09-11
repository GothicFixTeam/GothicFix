#ifndef _PATCH_UTILS_
#define _PATCH_UTILS_

class Timer
{
private:
	LARGE_INTEGER StartTime;
	LARGE_INTEGER Frequency;

public:
	void		Start(void) { QueryPerformanceCounter(&StartTime); };
	LONGLONG	GetPrecision(void) { return Frequency.QuadPart; };

	float		GetElapsedTimeSeconds(void)
	{
		LARGE_INTEGER CurrentTime;
		QueryPerformanceCounter(&CurrentTime);

		return float(CurrentTime.QuadPart - StartTime.QuadPart) / Frequency.QuadPart;
	}

public:
	Timer(void) 
	{
		QueryPerformanceFrequency(&Frequency); 
	};
	virtual ~Timer(void) {};
};

extern void RedirectIOToConsole(void);

extern bool GetModuleFileNameString(HMODULE hModule, TString& filename);

extern bool GetGothicWindowSize(POINT& size);

extern bool IsVdfs(void);
extern bool IsSpacer(void);

#define EXE_CRC_GOTHIC2_NOTR_REPORT_V2 0x2BCD7E30
#define EXE_CRC_GOTHIC2_FIX 0xA2EE682C
#define EXE_CRC_GOTHIC_MOD 0x225BA11E
#define EXE_CRC_GOTHIC_MOD_PATCHED 0x1F8D4811
#define EXE_CRC_GOTHIC 0x2C75C07A

extern uLong GetExeCrc32(void);

#define CODE_CRC_GOTHIC 0xF6DD31C4

extern uLong GetSectionCrc32(const char* name);
extern const uChar* GetSectionAddress(const uChar* codeBase, const char* name, size_t& size);

extern bool HasVgaVendor(DWORD ven);

extern bool Patch(uChar* data, size_t size, uChar* org, uChar* patch);

template<typename type>
bool PatchAddress(type* address, type value)
{
	DWORD OldProtect = 0;
	if(VirtualProtect(address, sizeof(type), PAGE_READWRITE, &OldProtect))
	{
		*address = value;
		VirtualProtect(address, sizeof(type), OldProtect, &OldProtect);
		return true;
	}
	return false;
}

extern DWORD GetImportSize(const uChar* codeBase);
extern PIMAGE_IMPORT_DESCRIPTOR GetImportDescriptor(const uChar* codeBase, const char* name);
extern FARPROC* GetImportFunctionAddress(const uChar* codeBase, PIMAGE_IMPORT_DESCRIPTOR importDesc, bool ordinal, const char* name);

template<typename type>
bool PatchImportFunctionAddress(const uChar* codeBase, PIMAGE_IMPORT_DESCRIPTOR importDesc, bool ordinal, const char* name, type value)
{
	FARPROC* Func = GetImportFunctionAddress(codeBase, importDesc, ordinal, name);
	if(Func)
		return PatchAddress<FARPROC>(Func, value);
	return false;
}

#endif