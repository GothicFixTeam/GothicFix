#ifndef _COMMON_UTILITY_EX_
#define _COMMON_UTILITY_EX_

namespace COMMON
{

// Platform independence functions
extern bool PlatformGetComputerName(TString& name);
extern uInt PlatformGetCurrentProcessId(void);
extern uInt PlatformGetCurrentThreadId(void);

extern bool PlatformGetWorkPath(TString& path);
extern bool PlatformGetTempPath(TString& path);
extern bool PlatformGetTempFileName(TString& name);
extern bool PlatformGetExePath(TString& name);

}

#endif