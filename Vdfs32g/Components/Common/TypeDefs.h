#ifndef _COMMON_TYPE_DEFS_
#define _COMMON_TYPE_DEFS_

namespace COMMON
{

typedef unsigned char Byte;
typedef unsigned char uChar;

typedef __int16				Int16;
typedef unsigned __int16	uInt16;
typedef __int32				Int32;
typedef unsigned __int32	uInt32;
typedef __int64				Int64;
typedef unsigned __int64	uInt64;

typedef unsigned int   uInt;
typedef unsigned long  uLong;
typedef unsigned short uShort;

#define dcast dynamic_cast
#define rcast reinterpret_cast
#define scast static_cast
#define ccast const_cast

#define COMMON_MAX_PATH 256

// TCHAR extensions
#ifdef _UNICODE
#define _ttof _wtof
#define _ttoi _wtoi
#define _tcstombs(dest, src, max_len) wcstombs(dest, src, max_len)
#define _mbstotcs(dest, src, max_len) mbstowcs((wchar_t*)dest, src, max_len)
#define _mbstotcs_l(dest, src, max_len, locale) _mbstowcs_l((wchar_t*)dest, src, max_len, locale)
#define _tcstombs_l(dest, src, max_len, locale) _wcstombs_l(dest, src, max_len, locale)
#define _wcstotcs(dest, src, max_len) wcscpy_s((wchar_t*)dest, max_len, src)
#define _tcstowcs(dest, src, max_len) wcscpy_s((wchar_t*)dest, max_len, src)
#else
#define _ttof atof
#define _ttoi atoi
#define _tcstombs(dest, src, max_len) strcpy_s(dest, max_len, src)
#define _mbstotcs(dest, src, max_len) strcpy_s(dest, max_len, src)
#define _mbstotcs_l(dest, src, max_len, locale) strcpy_s(dest, max_len, src)
#define _tcstombs_l(dest, src, max_len, locale) strcpy_s(dest, max_len, src)
#define _wcstotcs(dest, src, max_len) wcstombs(dest, src, max_len)
#define _tcstowcs(dest, src, max_len) mbstowcs(dest, src, max_len)
#endif

}

#endif