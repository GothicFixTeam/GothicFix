#ifndef _STD_FLOW_
#define _STD_FLOW_

class StdFlow : public IFS
{
protected:
	HANDLE FileHandle = INVALID_HANDLE_VALUE;

	ObjectArray<AutoPtr<StdFlow>> Streams;

protected:
	uInt		BuildIndex(const TCHAR* dir, VdfsIndex* index);
	StdFlow*	GetFreeStream(void);

protected:
	virtual uLong	Read(uLong offset, void* buffer, uLong size);

public:
	virtual int	GetType(void) const;

public:
	virtual VdfsIndex::FileInfo*	GetFileInfo(const AString& filename);
	virtual bool					FileExists(const AString& filename);

	virtual bool	UpdateFileIndex(const AString& file, uInt size, bool failifexists, VdfsIndex* index);
	virtual bool	UpdateIndex(VdfsIndex* index);

	virtual IFS*	Open(VdfsIndex::FileInfoPtr& fileinfo);
	virtual uLong	GetFileSize(void) const;
	virtual void	Close(void);

public:
	virtual uInt	GetStreamsSize(void) { return Streams.Size(); };

public:
	bool Init(VdfsIndex::FileInfoPtr& fileinfo);

	StdFlow(void);
	virtual ~StdFlow(void);
};

inline int StdFlow::GetType(void) const
{
	return IFS_TYPE_STDIO;
}

inline uLong StdFlow::GetFileSize(void) const
{
	return (CurrentFileInfo ? CurrentFileInfo->Size : 0);
}

inline StdFlow::StdFlow(void) 
{ 
	Name = "stdio"; 
	FileHandle = INVALID_HANDLE_VALUE;
	CurrentFileInfo = NULL; 
}

inline StdFlow::~StdFlow(void)
{
	Close();
}

#endif