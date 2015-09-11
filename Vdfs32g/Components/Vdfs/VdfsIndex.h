#ifndef _VDFS_INDEX_
#define _VDFS_INDEX_

class IFS;

class VdfsIndex : public Object
{
public:
	class FileInfo : public Object
	{
	public:
		AString	Name;
		uInt	Size;
		IFS*	Flow;
		uInt	Offset;

	public:
		FileInfo(void) { Size = 0; Flow = NULL; Offset = 0; };
		virtual ~FileInfo(void) {};
	};

	typedef TunablePtr<FileInfo> FileInfoPtr;

public:
	ObjectArray<FileInfoPtr>	Files;
	HashTable<uInt>				FullIndexes;
	HashTable<uInt>				FileIndexes;

public:
	FileInfo* GetFileInfo(const AString& filename)
	{
		uInt Index = FullIndexes[filename];
		if(Index)
			return Files[Index - 1];
		return NULL;
	}

	bool SearchFile(const AString& filename, char* fullname)
	{
		uInt Index = FileIndexes[filename];
		if(Index)
		{
			strncpy(fullname, &Files[Index - 1]->Name.GetData()[1], Files[Index - 1]->Name.Length() - 1);
			fullname[Files[Index - 1]->Name.Length() - 1] = '\0';
			return true;
		}
		return false;
	}

public:
	void Clear(void)
	{
		Files.Clear();
		FileIndexes.Clear();
		FullIndexes.Clear();
	}

	VdfsIndex(void) { };
	virtual ~VdfsIndex(void) { Clear(); };
};

typedef AutoPtr<VdfsIndex> VdfsIndexPtr;

#endif