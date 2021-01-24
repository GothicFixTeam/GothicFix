#include "PreCompiled.h"

uInt VdfFlow::BuildVdfsIndex(VdfsIndex* index, VdfEntryInfo* Entries, uInt BeginNum, const char* Directory)
{
	uInt result = 0;
	for(uInt i = BeginNum; ; i++)
	{
		// Make name null terminated
		for(uInt n = 63; n >= 0; n--)
		{
			if(Entries[i].Name[n] != 0x20) 
			{
				if(n != 63)
					Entries[i].Name[n + 1] = '\0';
				else
				{
					Entries[i].Name[n] = '\0';
					// Invalid name lengh > 64
				}
				break;
			}
		}

		AString Name(Directory);
		if(Name) Name += '\\';
		Name += Entries[i].Name;

		if(Entries[i].Type & VDF_ENTRY_DIR)
		{
			result += BuildVdfsIndex(index, Entries, Entries[i].JumpTo, Name);
		}
		else
		{
			AString FullName("\\");
			FullName += Name;
			if(!index->FullIndexes[FullName])
			{
				VdfsIndex::FileInfo* Info = index->Files.Add(new VdfsIndex::FileInfo);
				Info->Flow = this;
				Info->Name = FullName;
				Info->Offset = Entries[i].JumpTo;
				Info->Size = Entries[i].Size;
				index->FullIndexes[Info->Name] = index->Files.Size();

				uInt FileIndex = index->FileIndexes[Entries[i].Name];
				if(!FileIndex || (strcmp(FullName, index->Files[FileIndex - 1]->Name) < 0))
					index->FileIndexes[Entries[i].Name] = index->Files.Size();

				result++;
			}
		}

		if(Entries[i].Type & VDF_ENTRY_LAST)
			break;
	}
	return result;
}

bool VdfFlow::UpdateIndex(VdfsIndex* index)
{
	if(Archive)
	{
		// Read root catalog. Possible problem - NumEntries = 1, then add check for this with new without []
		DWORD readed = 0;
		VdfEntryInfo* Entries = new VdfEntryInfo[Header.NumEntries];
		size_t EntriesSize = Header.NumEntries * sizeof(VdfEntryInfo);
		if(!ReadFile(Archive, Entries, EntriesSize, &readed, NULL) || (readed != EntriesSize))
		{
			delete[] Entries;
			return false;
		}

		index->Files.Reserve(Header.NumFiles);

		// Build FileInfo HashTable
		if(!BuildVdfsIndex(index, Entries))
		{
			delete[] Entries;
			return false;
		}

		delete[] Entries;
		return true;
	}
	return false;
}

VdfFlow* VdfFlow::GetFreeStream(void)
{
	for(uInt i = 0; i < Streams.Size(); i++)
	{
		if(!Streams[i]->CurrentFileInfo)
			return Streams[i];
	}
	return Streams.Add(new VdfFlow());
}

IFS* VdfFlow::Open(VdfsIndex::FileInfoPtr& fileinfo)
{
	if(fileinfo && (fileinfo->Flow == this))
	{
		VdfFlow* Result = GetFreeStream();
		if(Result->Init(Name, fileinfo))
			return Result;
	}
	return NULL;
}

uLong VdfFlow::Read(uLong offset, void* buffer, uLong size)
{
	if(CurrentFileInfo)
	{
		if(SetFilePointer(Archive, CurrentFileInfo->Offset + offset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
			return 0;

		DWORD readed = 0;
		if(size && ReadFile(Archive, buffer, size, &readed, NULL) && (readed == size))
			return size;
	}
	return 0;
}

bool VdfFlow::Init(const TCHAR* arcname)
{
	if(Archive != INVALID_HANDLE_VALUE)
		return false;

	HANDLE hFile = CreateFile(arcname, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hFile != INVALID_HANDLE_VALUE)
	{
		// Read and verify header, set offset to root catalog
		DWORD readed = 0;
		if(ReadFile(hFile, &Header, sizeof(VdfHeader), &readed, NULL) && (readed == sizeof(VdfHeader)))
		{
			if(!memcmp(Header.Signature, VDF_SIGNATURE_G2, sizeof(Header.Signature)) && (Header.Version == 0x50) && (SetFilePointer(hFile, Header.RootCatOffset, NULL, FILE_BEGIN) != INVALID_SET_FILE_POINTER))
				Version = 2;
			else
			if(!memcmp(Header.Signature, VDF_SIGNATURE_G1, sizeof(Header.Signature)) && (Header.Version == 0x50) && (SetFilePointer(hFile, Header.RootCatOffset, NULL, FILE_BEGIN) != INVALID_SET_FILE_POINTER))
				Version = 1;
			else
			{
				memset(&Header, 0, sizeof(VdfHeader));
				CloseHandle(hFile);
				return false;
			}
		}

		Name = arcname;
		Archive = hFile;

		Streams.Add(new VdfFlow());
		return true;
	}
	return false;
}

bool VdfFlow::Init(const TCHAR* arcname, VdfsIndex::FileInfoPtr& fileinfo)
{
	if(CurrentFileInfo)
		return false;

	if(Archive != INVALID_HANDLE_VALUE)
	{
		CurrentFileInfo = fileinfo;
		Name = fileinfo->Name;
		return true;
	}

	HANDLE hFile = CreateFile(arcname, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hFile != INVALID_HANDLE_VALUE)
	{
		CurrentFileInfo = fileinfo;
		Archive = hFile;
		Name = fileinfo->Name;
		return true;
	}
	return false;
}

VdfFlow::VdfFlow(void)
{
	Archive = INVALID_HANDLE_VALUE;
	CurrentFileInfo = NULL;
	CurrentOffset = 0;
	Version = 0;
}

VdfFlow::~VdfFlow(void)
{
	Close();
	if(Archive != INVALID_HANDLE_VALUE)
	{
		Name.Clear();
		CloseHandle(Archive);
		Archive = INVALID_HANDLE_VALUE;
	}
	memset(&Header, 0, sizeof(VdfHeader));
}