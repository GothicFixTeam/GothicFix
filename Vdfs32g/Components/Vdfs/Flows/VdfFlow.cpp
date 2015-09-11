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
		VdfEntryInfo* Entries = new VdfEntryInfo[Header.NumEntries];
		size_t EntriesSize = Header.NumEntries * sizeof(VdfEntryInfo);
		if(fread(Entries, 1, EntriesSize, Archive) != EntriesSize)
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
		if(fseek(Archive, CurrentFileInfo->Offset + offset, SEEK_SET) != 0)
			return 0;

		if(size && (fread(buffer, 1, size, Archive) == size))
			return size;
	}
	return 0;
}

bool VdfFlow::Init(const TCHAR* arcname)
{
	if(Archive)
		return false;

	FILE* archive = NULL;
	if(!_tfopen_s(&archive, arcname, _T("rb")))
	{
		// Read and verify header, set offset to root catalog
		if(fread(&Header, 1, sizeof(VdfHeader), archive) == sizeof(VdfHeader))
		{
			if(!memcmp(Header.Signature, VDF_SIGNATURE_G2, sizeof(Header.Signature)) && (Header.Version == 0x50) && (!fseek(archive, Header.RootCatOffset, SEEK_SET)))
				Version = 2;
			else
			if(!memcmp(Header.Signature, VDF_SIGNATURE_G1, sizeof(Header.Signature)) && (Header.Version == 0x50) && (!fseek(archive, Header.RootCatOffset, SEEK_SET)))
				Version = 1;
			else
			{
				memset(&Header, 0, sizeof(VdfHeader));
				fclose(archive);
				return false;
			}
		}

		Name = arcname;
		Archive = archive;

		Streams.Add(new VdfFlow());
		return true;
	}
	return false;
}

bool VdfFlow::Init(const TCHAR* arcname, VdfsIndex::FileInfoPtr& fileinfo)
{
	if(CurrentFileInfo)
		return false;

	if(Archive)
	{
		CurrentFileInfo = fileinfo;
		Name = fileinfo->Name;
		return true;
	}

	FILE* archive = NULL;
	if(!_tfopen_s(&archive, arcname, _T("rb")))
	{
		CurrentFileInfo = fileinfo;
		Archive = archive;
		Name = fileinfo->Name;
		return true;
	}
	return false;
}

VdfFlow::VdfFlow(void)
{
	Archive = NULL;
	CurrentFileInfo = NULL;
	CurrentOffset = 0;
	Version = 0;
}

VdfFlow::~VdfFlow(void)
{
	Close();
	if(Archive)
	{
		Name.Clear();
		fclose(Archive);
		Archive = NULL;
	}
	memset(&Header, 0, sizeof(VdfHeader));
}