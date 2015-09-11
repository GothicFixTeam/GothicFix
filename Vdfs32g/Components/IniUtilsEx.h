#ifndef _INI_UTILS_EX_
#define _INI_UTILS_EX_

extern uInt ReadIniSections(AStringArray& sections, const TCHAR* file);
extern uInt ReadIniSectionParams(TaggedArray<AString, AString>& params, const char* section, const TCHAR* file);

#endif