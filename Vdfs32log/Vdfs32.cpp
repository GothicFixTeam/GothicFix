#include "Vdfs32.h"
#include <stdio.h>
#include <windows.h>

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

typedef long (_cdecl* vdf_fopen_func)(const char* filename, long flags);
typedef long (_cdecl* vdf_fclose_func)(long fp);
typedef long (_cdecl* vdf_fread_func)(long fp, char* buffer, long size);
typedef long (_cdecl* vdf_fseek_func)(long fp, long offset);
typedef long (_cdecl* vdf_ftell_func)(long fp);
typedef long (_cdecl* vdf_fexists_func)(const char* filename, long flags);
typedef long (_cdecl* vdf_searchfile_func)(const char* path, char* filename);
typedef long (_cdecl* vdf_getlasterror_func)(char* text);
typedef long (_cdecl* vdf_initall_func)(long numdisks, const char* cdid, long* cddrives, long* disksfound);
typedef long (_cdecl* vdf_exitall_func)(void);
typedef long (_cdecl* vdf_ffilesize_func)(int fp);

typedef long (_cdecl* vdf_getdir_func)(char* dirname);
typedef long (_cdecl* vdf_findopen_func)(const char* path, long flags);
typedef long (_cdecl* vdf_findnext_func)(long find, TVDFFINDDATA* finddata);
typedef long (_cdecl* vdf_findclose_func)(long find);

HMODULE hDLL = NULL;
vdf_fopen_func vdf_fopen_ptr = NULL;
vdf_fclose_func vdf_fclose_ptr = NULL;
vdf_fread_func vdf_fread_ptr = NULL;
vdf_fseek_func vdf_fseek_ptr = NULL;
vdf_ftell_func vdf_ftell_ptr = NULL;
vdf_fexists_func vdf_fexists_ptr = NULL;
vdf_getdir_func vdf_getdir_ptr = NULL;
vdf_findopen_func vdf_findopen_ptr = NULL;
vdf_findnext_func vdf_findnext_ptr = NULL;
vdf_findclose_func vdf_findclose_ptr = NULL;
vdf_searchfile_func vdf_searchfile_ptr = NULL;
vdf_getlasterror_func vdf_getlasterror_ptr = NULL;
vdf_initall_func vdf_initall_ptr = NULL;
vdf_exitall_func vdf_exitall_ptr = NULL;
vdf_ffilesize_func vdf_ffilesize_ptr = NULL;

FILE* Log = NULL;

long _cdecl vdf_fopen(const char* filename, long flags) 
{
	Timer Measure;
	Measure.Start();
	long res = vdf_fopen_ptr(filename, flags);
	fprintf(Log, "%d vdf_fopen(%s, %d)\n", res, filename, flags);
	fprintf(Log, "\t%f sec\n", Measure.GetElapsedTimeSeconds());
	fflush(Log);
	return res;
}

long _cdecl vdf_fclose(long fp) 
{
	Timer Measure;
	Measure.Start();
	long res = vdf_fclose_ptr(fp);
	fprintf(Log, "%d vdf_fclose(%d)\n", res, fp);
	fprintf(Log, "\t%f sec\n", Measure.GetElapsedTimeSeconds());
	fflush(Log);
	return res; 
}

long _cdecl vdf_fread(long fp, char* buffer, long size) 
{
	Timer Measure;
	Measure.Start();
	long res = vdf_fread_ptr(fp, buffer, size);
	//fprintf(Log, "%d vdf_fread(%d, %d, %d)\n", res, fp, buffer, size);
	//fprintf(Log, "\t%f sec\n", Measure.GetElapsedTimeSeconds());
	//fflush(Log);
	return res; 
}

long _cdecl vdf_fseek(long fp, long offset) 
{
	Timer Measure;
	Measure.Start();
	long res = vdf_fseek_ptr(fp, offset);
	//fprintf(Log, "%d vdf_fseek(%d, %d)\n", res, fp, offset);
	//fprintf(Log, "\t%f sec\n", Measure.GetElapsedTimeSeconds());
	//fflush(Log);
	return res; 
}

long _cdecl vdf_ftell(long fp) 
{
	Timer Measure;
	Measure.Start();
	long res = vdf_ftell_ptr(fp);
	//fprintf(Log, "%d vdf_ftell(%d)\n", res, fp);
	//fprintf(Log, "\t%f sec\n", Measure.GetElapsedTimeSeconds());
	//fflush(Log);
	return res; 
}

long _cdecl vdf_fexists(const char* filename, long flags) 
{
	Timer Measure;
	Measure.Start();
	long res = vdf_fexists_ptr(filename, flags);
	fprintf(Log, "%d vdf_fexists(%s, %d)\n", res, filename, flags);
	fprintf(Log, "\t%f sec\n", Measure.GetElapsedTimeSeconds());
	fflush(Log);
	return res; 
}

long _cdecl vdf_searchfile(const char* filename, char* fullname) 
{
	Timer Measure;
	Measure.Start();
	long res = vdf_searchfile_ptr(filename, fullname);
	fprintf(Log, "%d vdf_searchfile(%s, %s)\n", res, filename, fullname);
	fprintf(Log, "\t%f sec\n", Measure.GetElapsedTimeSeconds());
	fflush(Log);
	return res;
};

long _cdecl vdf_getlasterror(char* text)
{
	Timer Measure;
	Measure.Start();
	long res = vdf_getlasterror_ptr(text);
	fprintf(Log, "%d vdf_getlasterror(%s)\n", res, text);
	fprintf(Log, "\t%f sec\n", Measure.GetElapsedTimeSeconds());
	fflush(Log);
	return res;
}

long _cdecl vdf_initall(int numdisks, const char* cdid, long* cddrives, long* disksfound)
{
	Timer Measure;
	Measure.Start();
	if(hDLL = LoadLibrary(TEXT("Vdfs32org.dll")))
	{
		vdf_fopen_ptr = (vdf_fopen_func)GetProcAddress(hDLL, "vdf_fopen");
		vdf_fclose_ptr = (vdf_fclose_func)GetProcAddress(hDLL, "vdf_fclose");
		vdf_fread_ptr = (vdf_fread_func)GetProcAddress(hDLL, "vdf_fread");
		vdf_fseek_ptr = (vdf_fseek_func)GetProcAddress(hDLL, "vdf_fseek");
		vdf_ftell_ptr = (vdf_ftell_func)GetProcAddress(hDLL, "vdf_ftell");
		vdf_fexists_ptr = (vdf_fexists_func)GetProcAddress(hDLL, "vdf_fexists");
		vdf_getdir_ptr = (vdf_getdir_func)GetProcAddress(hDLL, "vdf_getdir");
		vdf_findopen_ptr = (vdf_findopen_func)GetProcAddress(hDLL, "vdf_findopen");
		vdf_findnext_ptr = (vdf_findnext_func)GetProcAddress(hDLL, "vdf_findnext");
		vdf_findclose_ptr = (vdf_findclose_func)GetProcAddress(hDLL, "vdf_findclose");
		vdf_searchfile_ptr = (vdf_searchfile_func)GetProcAddress(hDLL, "vdf_searchfile");
		vdf_getlasterror_ptr = (vdf_getlasterror_func)GetProcAddress(hDLL, "vdf_getlasterror");
		vdf_initall_ptr = (vdf_initall_func)GetProcAddress(hDLL, "vdf_initall");
		vdf_exitall_ptr = (vdf_exitall_func)GetProcAddress(hDLL, "vdf_exitall");
		vdf_ffilesize_ptr = (vdf_ffilesize_func)GetProcAddress(hDLL, "vdf_ffilesize");

		fopen_s(&Log, "VDFS.log", "w");

		long res = vdf_initall_ptr(numdisks, cdid, cddrives, disksfound);
		fprintf(Log, "%d vdf_initall(%d, %s, %d, %d)\n", res, numdisks, cdid, *cddrives, *disksfound);
		fprintf(Log, "\t%f sec\n", Measure.GetElapsedTimeSeconds());
		fflush(Log);
		return res;
	}
	return -1;
}

long _cdecl vdf_exitall(void) 
{
	Timer Measure;
	Measure.Start();
	if(hDLL)
	{
		long res = vdf_exitall_ptr();
		fprintf(Log, "%d vdf_exitall()\n", res);
		fprintf(Log, "\t%f sec\n", Measure.GetElapsedTimeSeconds());
		fflush(Log);

		vdf_fopen_ptr = NULL;
		vdf_fclose_ptr = NULL;
		vdf_fread_ptr = NULL;
		vdf_fseek_ptr = NULL;
		vdf_ftell_ptr = NULL;
		vdf_fexists_ptr = NULL;
		vdf_getdir_ptr = NULL;
		vdf_findopen_ptr = NULL;
		vdf_findnext_ptr = NULL;
		vdf_findclose_ptr = NULL;
		vdf_searchfile_ptr = NULL;
		vdf_getlasterror_ptr = NULL;
		vdf_initall_ptr = NULL;
		vdf_exitall_ptr = NULL;
		vdf_ffilesize_ptr = NULL;

		FreeLibrary(hDLL);
		hDLL = NULL;

		fclose(Log);
		Log =  NULL;

		return res;
	}
	return 0;
}

long _cdecl vdf_ffilesize(long fp) 
{
	Timer Measure;
	Measure.Start();
	long res = vdf_ffilesize_ptr(fp);
	//fprintf(Log, "%d vdf_ffilesize(%d)\n", res, fp);
	//fprintf(Log, "\t%f sec\n", Measure.GetElapsedTimeSeconds());
	fflush(Log);
	return res;
}

// Not implemented

long _cdecl vdf_getdir(char* dirname) 
{
	Timer Measure;
	Measure.Start();
	long res = vdf_getdir_ptr(dirname);
	fprintf(Log, "%d vdf_getdir_ptr(%s)\n", res, dirname);
	fprintf(Log, "\t%f sec\n", Measure.GetElapsedTimeSeconds());
	fflush(Log);
	return res;
}

long _cdecl vdf_findopen(const char* path, long flags) 
{
	Timer Measure;
	Measure.Start();
	long res = vdf_findopen_ptr(path, flags);
	fprintf(Log, "%d vdf_findopen(%s, %d)\n", res, path, flags);
	fprintf(Log, "\t%f sec\n", Measure.GetElapsedTimeSeconds());
	fflush(Log);
	return res;
}

long _cdecl vdf_findnext(long find, TVDFFINDDATA* finddata) 
{
	Timer Measure;
	Measure.Start();
	long res = vdf_findnext_ptr(find, finddata);
	fprintf(Log, "%d vdf_findnext(%d, %s)\n", res, find, finddata->name);
	fprintf(Log, "\t%f sec\n", Measure.GetElapsedTimeSeconds());
	fflush(Log);
	return res;
}

long _cdecl vdf_findclose(long find) 
{
	Timer Measure;
	Measure.Start();
	long res = vdf_findclose_ptr(find);
	fprintf(Log, "%d vdf_findclose(%d)\n", res, find);
	fprintf(Log, "\t%f sec\n", Measure.GetElapsedTimeSeconds());
	fflush(Log);
	return res;
}