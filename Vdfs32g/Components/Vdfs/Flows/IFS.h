#ifndef _IFS_
#define _IFS_

#define VDFS_BUFFER_SIZE 10000

#define IFS_TYPE_STDIO	1
#define IFS_TYPE_VDF	2

class IfsBase : public Object
{
public:
	virtual uLong	GetFileSize(void) const = 0;
	virtual uLong	GetOffset(void) const = 0;
	virtual bool	SetOffset(uLong offset) = 0;
	virtual uLong	GetData(void* buffer, uLong size) = 0;
	virtual void	Close(void) = 0;
};

class IFS : public IfsBase
{
protected:
	class IfsBuffer
	{
	public:
		uLong	Begin;
		Byte	Data[VDFS_BUFFER_SIZE];
		uLong	Size;

	public:
		void Reset(void)
		{
			Begin = 0;
			Size = 0;
		}

	public:
		IfsBuffer(void)
		{
			Begin = 0;
			Size = 0;
		}

		~IfsBuffer(void)
		{
		}
	};

protected:
	TString Name;

	VdfsIndex::FileInfoPtr	CurrentFileInfo;
	uLong					CurrentOffset;
	IfsBuffer				Buffer;

protected:
	virtual uLong	Read(uLong offset, void* buffer, uLong size) = 0;

public:
	virtual const TCHAR*	GetName(void) const;
	virtual int				GetType(void) const = 0;

public:
	virtual VdfsIndex::FileInfo*	GetFileInfo(const AString& filename) { return NULL; };
	virtual bool					FileExists(const AString& filename) { return false; };

	virtual bool	UpdateIndex(VdfsIndex* index) = 0;

	virtual IFS*	Open(VdfsIndex::FileInfoPtr& fileinfo) = 0;
	virtual uLong	GetFileSize(void) const = 0;
	virtual uLong	GetOffset(void) const;
	virtual bool	SetOffset(uLong offset);
	virtual uLong	GetData(void* buffer, uLong size);
	virtual void	Close(void);

public:
	virtual uInt	GetStreamsSize(void) { return 0; };

public:
	IFS(void) { CurrentOffset = 0; };
	virtual ~IFS(void) {};
};

inline const TCHAR* IFS::GetName(void) const
{
	return Name;
}

inline uLong IFS::GetOffset(void) const
{
	return CurrentOffset;
}

inline bool	IFS::SetOffset(uLong offset)
{
	if(offset <= GetFileSize())
	{
		CurrentOffset = offset;
		return true;
	}
	return false;
}

inline void IFS::Close(void)
{
	CurrentFileInfo = NULL;
	CurrentOffset = 0;
	Buffer.Reset();
}

inline uLong IFS::GetData(void* buffer, uLong size)
{
	if(!size)
		return 0;

	if(size > VDFS_BUFFER_SIZE)
	{
		if(Read(CurrentOffset, buffer, size))
		{
			CurrentOffset += size;
			return size;
		}
		return 0;
	}

	if((CurrentOffset < Buffer.Begin) || (CurrentOffset + size >= Buffer.Begin + Buffer.Size))
	{
		Buffer.Reset();
		uLong SizeToRead = MIN(VDFS_BUFFER_SIZE, GetFileSize() - CurrentOffset);
		if(!Read(CurrentOffset, Buffer.Data, SizeToRead))
			return 0;
		Buffer.Begin = CurrentOffset;
		Buffer.Size = SizeToRead;
	}

	memcpy(buffer, &Buffer.Data[CurrentOffset - Buffer.Begin], size);
	CurrentOffset += size;
	return size;
}

typedef AutoPtr<IFS> IfsPtr;

class IfsFilter : public IfsBase
{
public:
	virtual IfsFilter* Open(IFS* src) = 0;
};

typedef AutoPtr<IfsFilter> IfsFilterPtr;

#endif