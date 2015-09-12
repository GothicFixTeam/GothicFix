#ifndef _VDFS_
#define _VDFS_

class Vdfs : public Object
{
protected:
	CRITICAL_SECTION CS;

	VdfsIndexPtr		Index;

	IFS*				PhysicalFlow;
	ObjectArray<IfsPtr>	VirtualFlows;

	ObjectArray<IfsFilterPtr> Filters;

	AString	LastError;

protected:
	void EnumDirs(const TCHAR* dir, TStringArray& dirs, bool recurse);
	void MountDir(const TCHAR* dir, const TCHAR* ext);

	IfsBase* ApplyFilter(IFS* src);

public:
	virtual long FileExist(const char* filename, long flags);
	virtual bool SearchFile(const char* filename, char* fullname);
	virtual IfsBase* OpenFile(const char* filename, long flags);
	virtual void CloseFile(IfsBase* fp);

	virtual void SetLastError(const char* text) { EnterCriticalSection(&CS); LastError = text; LeaveCriticalSection(&CS); };
	virtual void GetLastError(char* text) { EnterCriticalSection(&CS); strncpy(text, LastError.GetData(), LastError.Length()); text[LastError.Length()] = '\0'; LeaveCriticalSection(&CS); };

public:
	virtual bool UpdateStdFileIndex(const AString& file, uInt size);
	virtual bool InitVirtual(void);
	virtual bool Init(void);
	virtual void Clear(void); 

public:
	Vdfs(void);
	virtual ~Vdfs(void);
};

#endif