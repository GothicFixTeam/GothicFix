#include "PreCompiled.h"

HMODULE hModule = NULL;

typedef M3D_PROVIDER (__stdcall* RIB_alloc_provider_handleFunc)(uInt module);
RIB_alloc_provider_handleFunc RIB_alloc_provider_handleFuncPtr = NULL;
M3D_PROVIDER __stdcall RIB_alloc_provider_handle(uInt module)
{
	return RIB_alloc_provider_handleFuncPtr(module);
}

typedef M3D_PROVIDER (__stdcall* RIB_provider_library_handleFunc)(void);
RIB_provider_library_handleFunc RIB_provider_library_handleFuncPtr = NULL;
M3D_PROVIDER __stdcall RIB_provider_library_handle(void)
{
	if(RIB_provider_library_handleFuncPtr)
		return RIB_provider_library_handleFuncPtr();
	return RIB_alloc_provider_handle(0);
}

typedef M3D_RESULT (__stdcall* RIB_register_interfaceFunc)(M3D_PROVIDER provider, const char* interface_name, int entry_count, M3D_INTERFACE_ENTRY const *rlist);
RIB_register_interfaceFunc RIB_register_interfaceFuncPtr = NULL;
M3D_RESULT __stdcall RIB_register_interface(M3D_PROVIDER provider, const char* interface_name, int entry_count, const M3D_INTERFACE_ENTRY* rlist)
{
	return RIB_register_interfaceFuncPtr(provider, interface_name, entry_count, rlist);
}

typedef M3D_RESULT (__stdcall* RIB_unregister_interfaceFunc)(M3D_PROVIDER provider, const char* interface_name, int entry_count, const M3D_INTERFACE_ENTRY* rlist);
RIB_unregister_interfaceFunc RIB_unregister_interfaceFuncPtr = NULL;
M3D_RESULT __stdcall RIB_unregister_interface(M3D_PROVIDER provider, const char* interface_name, int entry_count, M3D_INTERFACE_ENTRY const *rlist)
{
	return RIB_unregister_interfaceFuncPtr(provider, interface_name, entry_count, rlist);
}

typedef HTIMER (__stdcall* AIL_register_timerFunc)(MSS_TIMER_CALLBACK cb);
AIL_register_timerFunc AIL_register_timerFuncPtr = NULL;
HTIMER  __stdcall  AIL_register_timer(MSS_TIMER_CALLBACK cb)
{
	return AIL_register_timerFuncPtr(cb);
}

typedef uInt (__stdcall* AIL_set_timer_userFunc)(HTIMER timer, uInt user);
AIL_set_timer_userFunc AIL_set_timer_userFuncPtr = NULL;
uInt __stdcall AIL_set_timer_user(HTIMER timer, uInt user)
{
	return AIL_set_timer_userFuncPtr(timer, user);
}

typedef void (__stdcall* AIL_set_timer_frequencyFunc)(HTIMER timer, uInt hertz);
AIL_set_timer_frequencyFunc AIL_set_timer_frequencyFuncPtr = NULL;
void __stdcall AIL_set_timer_frequency(HTIMER timer, uInt hertz)
{
	AIL_set_timer_frequencyFuncPtr(timer, hertz);
}

typedef void (__stdcall* AIL_start_timerFunc)(HTIMER timer);
AIL_start_timerFunc AIL_start_timerFuncPtr = NULL;
void __stdcall AIL_start_timer(HTIMER timer)
{
	return AIL_start_timerFuncPtr(timer);
}

typedef void (__stdcall* AIL_stop_timerFunc)(HTIMER timer);
AIL_stop_timerFunc AIL_stop_timerFuncPtr = NULL;
void __stdcall AIL_stop_timer(HTIMER timer)
{
	AIL_stop_timerFuncPtr(timer);
}

typedef void (__stdcall* AIL_release_timer_handleFunc)(HTIMER timer);
AIL_release_timer_handleFunc AIL_release_timer_handleFuncPtr = NULL;
void __stdcall AIL_release_timer_handle(HTIMER timer)
{
	AIL_release_timer_handleFuncPtr(timer);
}

typedef int (__stdcall* AIL_get_preferenceFunc)(uInt number);
AIL_get_preferenceFunc AIL_get_preferenceFuncPtr = NULL;
int __stdcall AIL_get_preference(uInt number)
{
	return AIL_get_preferenceFuncPtr(number);
}

void MssFree(void)
{
	if(hModule)
	{
		RIB_alloc_provider_handleFuncPtr = NULL;
		RIB_provider_library_handleFuncPtr = NULL;
		RIB_register_interfaceFuncPtr = NULL;
		RIB_unregister_interfaceFuncPtr = NULL;

		AIL_register_timerFuncPtr = NULL;
		AIL_set_timer_userFuncPtr = NULL;
		AIL_set_timer_frequencyFuncPtr = NULL;
		AIL_start_timerFuncPtr = NULL;
		AIL_stop_timerFuncPtr = NULL;
		AIL_release_timer_handleFuncPtr = NULL;

		AIL_get_preferenceFuncPtr = NULL;

		FreeLibrary(hModule);
		hModule = NULL;
	}
}

bool MssLoad(void)
{
	if(hModule = LoadLibrary(_T("Mss32.dll")))
	{
		RIB_alloc_provider_handleFuncPtr = (RIB_alloc_provider_handleFunc)GetProcAddress(hModule, "RIB_alloc_provider_handle");
		RIB_provider_library_handleFuncPtr = (RIB_provider_library_handleFunc)GetProcAddress(hModule, "_RIB_provider_library_handle@0");
		RIB_register_interfaceFuncPtr = (RIB_register_interfaceFunc)GetProcAddress(hModule, "RIB_register_interface");
		RIB_unregister_interfaceFuncPtr = (RIB_unregister_interfaceFunc)GetProcAddress(hModule, "RIB_unregister_interface");

		AIL_register_timerFuncPtr = (AIL_register_timerFunc)GetProcAddress(hModule, "_AIL_register_timer@4");
		AIL_set_timer_userFuncPtr = (AIL_set_timer_userFunc)GetProcAddress(hModule, "_AIL_set_timer_user@8");
		AIL_set_timer_frequencyFuncPtr = (AIL_set_timer_frequencyFunc)GetProcAddress(hModule, "_AIL_set_timer_frequency@8");
		AIL_start_timerFuncPtr = (AIL_start_timerFunc)GetProcAddress(hModule, "_AIL_start_timer@4");
		AIL_stop_timerFuncPtr = (AIL_stop_timerFunc)GetProcAddress(hModule, "_AIL_stop_timer@4");
		AIL_release_timer_handleFuncPtr = (AIL_release_timer_handleFunc)GetProcAddress(hModule, "_AIL_release_timer_handle@4");

		AIL_get_preferenceFuncPtr = (AIL_get_preferenceFunc)GetProcAddress(hModule, "_AIL_get_preference@4");

		if((RIB_alloc_provider_handleFuncPtr || RIB_provider_library_handleFuncPtr) && RIB_register_interfaceFuncPtr && RIB_unregister_interfaceFuncPtr &&
			AIL_register_timerFuncPtr && AIL_set_timer_userFuncPtr && AIL_set_timer_frequencyFuncPtr && AIL_start_timerFuncPtr && AIL_stop_timerFuncPtr && AIL_release_timer_handleFuncPtr &&
				AIL_get_preferenceFuncPtr)
					return true;
	}
	MssFree();
	return false;
}