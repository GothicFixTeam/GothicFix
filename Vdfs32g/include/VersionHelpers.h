/******************************************************************
*                                                                 *
*  VersionHelpers.h -- This module defines helper functions to    *
*                      promote version check with proper          *
*                      comparisons.                               *
*                                                                 *
*  Copyright (c) Microsoft Corp.  All rights reserved.            *
*                                                                 *
******************************************************************/
#ifndef _versionhelpers_H_INCLUDED_
#define _versionhelpers_H_INCLUDED_

#ifdef _MSC_VER
#pragma once
#endif  // _MSC_VER

#include <specstrings.h>    // for _In_, etc.
#define _WIN32_WINNT_VISTA                  0x0600
#define _WIN32_WINNT_WIN7                   0x0601
#define _WIN32_WINNT_WIN8                   0x0602
#define _WIN32_WINNT_WINBLUE                0x0603

#if !defined(__midl) && !defined(SORTPP_PASS)

#if (NTDDI_VERSION >= NTDDI_WINXP)

#ifdef __cplusplus

#define VERSIONHELPERAPI inline bool

#else  // __cplusplus

#define VERSIONHELPERAPI FORCEINLINE BOOL

#endif // __cplusplus

#pragma comment(lib, "Version.lib")

inline bool KernelVersionNotLess(uInt major, uInt minor, uInt build, bool& res)
{
	bool Status = false;

	DWORD Tmp = 0;
	DWORD Size = GetFileVersionInfoSize(_T("kernel32.dll"), &Tmp);
	if(Size)
	{
		BYTE* Buffer = new BYTE[Size];
		if(GetFileVersionInfo(_T("kernel32.dll"), NULL, Size, Buffer))
		{
			struct LANGANDCODEPAGE {
			  WORD wLanguage;
			  WORD wCodePage;
			} *lpTranslate = { 0 };
			UINT cbTranslate = 0;

			VerQueryValue(Buffer, TEXT("\\VarFileInfo\\Translation"), (LPVOID*)&lpTranslate, &cbTranslate);
			if(cbTranslate/sizeof(struct LANGANDCODEPAGE) > 0)
			{
				LPTSTR file_version;
				UINT   cchLength;
				if(VerQueryValue(Buffer, TString().Format(_T("\\StringFileInfo\\%04x%04x\\FileVersion"), lpTranslate[0].wLanguage, lpTranslate[0].wCodePage), (void **)&file_version, &cchLength) && cchLength && file_version)
				{
					TStringArrayPtr Tokens = TString(file_version).GetAllTokens(_T("."));
					if(Tokens && Tokens->Size() > 2)
					{
						Status = true;

						res = (Tokens->GetElement(2).ToUInt() >= build);
						uInt Major = Tokens->GetElement(0).ToUInt();
						if(Major == major)
							res &= (Tokens->GetElement(1).ToUInt() >= minor);
						else
							res &= (Major >= major);
					}
				}
			}
		}
		delete[] Buffer;
	}
	return Status;
}

VERSIONHELPERAPI
IsWindowsVersionOrGreater(WORD wMajorVersion, WORD wMinorVersion, WORD wServicePackMajor)
{
    OSVERSIONINFOEXW osvi = { sizeof(osvi), 0, 0, 0, 0, {0}, 0, 0 };
    DWORDLONG        const dwlConditionMask = VerSetConditionMask(
        VerSetConditionMask(
        VerSetConditionMask(
            0, VER_MAJORVERSION, VER_GREATER_EQUAL),
               VER_MINORVERSION, VER_GREATER_EQUAL),
               VER_SERVICEPACKMAJOR, VER_GREATER_EQUAL);

    osvi.dwMajorVersion = wMajorVersion;
    osvi.dwMinorVersion = wMinorVersion;
    osvi.wServicePackMajor = wServicePackMajor;

    return VerifyVersionInfoW(&osvi, VER_MAJORVERSION | VER_MINORVERSION | VER_SERVICEPACKMAJOR, dwlConditionMask) != FALSE;
}

VERSIONHELPERAPI
IsWindowsXPOrGreater()
{
	bool NotLess = false;
	if(KernelVersionNotLess(HIBYTE(_WIN32_WINNT_WINXP), LOBYTE(_WIN32_WINNT_WINXP), 2600, NotLess))
		return NotLess;

    return IsWindowsVersionOrGreater(HIBYTE(_WIN32_WINNT_WINXP), LOBYTE(_WIN32_WINNT_WINXP), 0);
}

VERSIONHELPERAPI
IsWindowsVistaOrGreater()
{
	bool NotLess = false;
	if(KernelVersionNotLess(HIBYTE(_WIN32_WINNT_VISTA), LOBYTE(_WIN32_WINNT_VISTA), 6000, NotLess))
		return NotLess;

    return IsWindowsVersionOrGreater(HIBYTE(_WIN32_WINNT_VISTA), LOBYTE(_WIN32_WINNT_VISTA), 0);
}

VERSIONHELPERAPI
IsWindows7OrGreater()
{
	bool NotLess = false;
	if(KernelVersionNotLess(HIBYTE(_WIN32_WINNT_WIN7), LOBYTE(_WIN32_WINNT_WIN7), 7600, NotLess))
		return NotLess;

    return IsWindowsVersionOrGreater(HIBYTE(_WIN32_WINNT_WIN7), LOBYTE(_WIN32_WINNT_WIN7), 0);
}

VERSIONHELPERAPI
IsWindows8OrGreater()
{
	bool NotLess = false;
	if(KernelVersionNotLess(HIBYTE(_WIN32_WINNT_WIN8), LOBYTE(_WIN32_WINNT_WIN8), 9200, NotLess))
		return NotLess;

    return IsWindowsVersionOrGreater(HIBYTE(_WIN32_WINNT_WIN8), LOBYTE(_WIN32_WINNT_WIN8), 0);
}

VERSIONHELPERAPI
IsWindows8Point1OrGreater()
{
	bool NotLess = false;
	if(KernelVersionNotLess(HIBYTE(_WIN32_WINNT_WINBLUE), LOBYTE(_WIN32_WINNT_WINBLUE), 9200, NotLess))
		return NotLess;

    return IsWindowsVersionOrGreater(HIBYTE(_WIN32_WINNT_WINBLUE), LOBYTE(_WIN32_WINNT_WINBLUE), 0);
}

#endif // NTDDI_VERSION

#endif // defined(__midl)

#endif // _VERSIONHELPERS_H_INCLUDED_
