#ifndef _VDFS32_
#define _VDFS32_

#define VDF_VIRTUAL         1
#define VDF_PHYSICAL        2
#define VDF_PHYSICALFIRST   4
#define VDF_PACKED          8
#define VDF_NOBUFFER       16

#define VDF_OPTID_MAXFILES  0
#define VDF_OPTID_MAXBUFFER 1

typedef struct
{
  char  name[64];
  long  size;
  long  attr;
  long  datetime;
} TVDFFINDDATA;

extern long	_cdecl vdf_fopen(const char* filename, long flags);
extern long	_cdecl vdf_fclose(long fp);
extern long	_cdecl vdf_fread(long fp, char* buffer, long size);
extern long	_cdecl vdf_fseek(long fp, long offset);
extern long	_cdecl vdf_ftell(long fp);
extern long	_cdecl vdf_fexists(const char* filename, long flags);
extern long	_cdecl vdf_searchfile(const char* path, char* filename);
extern long	_cdecl vdf_getlasterror(char* text);
extern long	_cdecl vdf_initall(int numdisks, const char* cdid, long* cddrives, long* disksfound);
extern long	_cdecl vdf_exitall(void);
extern long	_cdecl vdf_ffilesize(long fp);

// Not implemented
extern long	_cdecl vdf_getdir(char* dirname);
extern long	_cdecl vdf_findopen(const char* path, long flags);
extern long	_cdecl vdf_findnext(long find, TVDFFINDDATA* finddata);
extern long	_cdecl vdf_findclose(long find);

// Internal
extern long _cdecl vdf_initall_internal(void);

// Not used
extern long _cdecl vdf_fseekrel(long fp, long offset);
extern long _cdecl vdf_fdirexist(char* pathname, long flags);
extern long _cdecl vdf_changedir(char* pathname);
extern long _cdecl vdf_setOption(long optid, long val);
extern long _cdecl vdf_GetOption(long optid);

#endif