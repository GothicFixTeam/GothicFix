#ifndef _COMMON_UTILITY_
#define _COMMON_UTILITY_

namespace COMMON
{

#ifdef _M_IX86
#define COMMON_PLATFORM "Win32"
#define COMMON_ARCH "x86"
#else
#define COMMON_PLATFORM "Win64"
#define COMMON_ARCH "x64"
#endif

// Base definitions and macros
#define MATH_EPS (1E-5)
#define MAX_FLOAT (3.402823466e+38f)
#define MATH_PI (3.14159265358979323846f)
#define MATH_DEG_TO_RAD(a) (((a)*MATH_PI)/180.0f)
#define MATH_RAD_TO_DEG(a) (((a)*180.0f)/MATH_PI)

#define NONE_TEXT (const TCHAR*)0
#define END_TEXT (const TCHAR*)1

#define ROUND(a)				((a < 0) ? floor(a) : ceil(a))
#define ABS(a)					((a < 0) ? -(a) : a) 
#define SQR(x)					((x) * (x))
#define MIN(x,y)				((x > y) ? y : x)
#define MAX(x,y)				((x > y) ? (x) : (y))
#define CLAMP(min, value, max)	((value < max) ? ((value > min) ? value : min) : max)
#define BIT(n)					(1 << n)

#define NUM_VER(v1,v2,v3,v4) \
	((v1 << 28) + (v2 << 24) + (v3 << 16) + v4)

#define ASTR_VER(ver) \
	(AString(ver >> 28) + AString(".") + AString((ver << 4) >> 28) + AString(".") \
	+ AString((ver << 8) >> 24) + AString(".") + AString((ver << 16) >> 16))

#define WSTR_VER(ver) \
	(WString(ver >> 28) + WString(L".") + WString((ver << 4) >> 28) + WString(L".") \
	+ WString((ver << 8) >> 24) + WString(L".") + WString((ver << 16) >> 16))

#define TSTR_VER(ver) \
	(TString(ver >> 28) + TString(_T(".")) + TString((ver << 4) >> 28) + TString(_T(".")) \
	+ TString((ver << 8) >> 24) + TString(_T(".")) + TString((ver << 16) >> 16))

#define MAKE_FOURCC(ch0, ch1, ch2, ch3) \
    ((uInt)(uChar)(ch0) | ((uInt)(uChar)(ch1) << 8) | \
    ((uInt)(uChar)(ch2) << 16) | ((uInt)(uChar)(ch3) << 24 ));

// Common functions
extern float FloatDivRemainder(float num, float div); 
extern uInt NearestToPower2(uInt Value);

extern uInt GetFirstSetBit(uInt Value);
extern uInt GetCountSetBit(uInt Value);

extern uChar	Crc8(const uChar* buf, uInt len, uChar crc = 0);
extern uShort	Crc16(const uChar* buf, uInt len, uShort crc = 0);
extern uLong	Crc32(const uChar *buf, uInt len, uLong crc = 0);

extern bool Encrypt8(uChar *buf, uLong len, const uChar* pass);
extern bool Decrypt8(uChar *buf, uLong len, const uChar* pass);

extern bool Encrypt8v2(uChar *buf, uLong len, const uChar* pass); // pass has to be null terminated; warning: byte pos sensitive
extern bool Decrypt8v2(uChar *buf, uLong len, const uChar* pass); // pass has to be null terminated; warning: byte pos sensitive

// crt strings extensions
extern const char* _strnstr(const char* _Str, const char* _SubStr, size_t _SubStrLen);
extern const char* _strnistr(const char* _Str, const char* _SubStr, size_t _SubStrLen);
extern const char* _strrnstr(const char* _Str, const char* _SubStr, size_t _StrLen, size_t _SubStrLen);

extern const wchar_t* _wcsnstr(const wchar_t* _Str, const wchar_t* _SubStr, size_t _SubStrLen);
extern const wchar_t* _wcsnistr(const wchar_t* _Str, const wchar_t* _SubStr, size_t _SubStrLen);
extern const wchar_t* _wcsrnstr(const wchar_t* _Str, const wchar_t* _SubStr, size_t _StrLen, size_t _SubStrLen);

// crt mem extensions 
extern const uChar* _memstr(const uChar* buffer, size_t bufsize, const uChar* str, size_t strsize);
extern const uChar* _memrstr(const uChar* buffer, size_t bufsize, const uChar* str, size_t strsize);

}

#endif