#ifndef _INI_UTILS_
#define _INI_UTILS_

extern bool ReadIniString(const char* section, const char* key, const char* defval, char* val, size_t size, const char* file);
extern bool WriteIniString(const char* section, const char* key, const char* val, const char* file);

// Extended
extern uInt ReadIniSections(AStringArray& sections, const TCHAR* file);
extern uInt ReadIniSectionParams(TaggedArray<AString, AString>& params, const char* section, const TCHAR* file);

extern bool GothicReadIniString(const char* section, const char* key, const char* defval, char* val, size_t size, const char* file);
extern bool GothicWriteIniString(const char* section, const char* key, const char* val, const char* file);

#endif