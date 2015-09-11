#include "PreCompiled.h"

uInt StdFlow::BuildIndex(const TCHAR* dir, VdfsIndex* index)
{
	uInt result = 0;

	TString SearchString(dir);
	SearchString += _T("*");

	WIN32_FIND_DATA findfiledata;
	findfiledata.cFileName[0] = _T('?');
	HANDLE hf = FindFirstFile(SearchString, &findfiledata);
	for(BOOL cont = true; (hf != INVALID_HANDLE_VALUE) && (cont != false); cont = FindNextFile(hf, (LPWIN32_FIND_DATA)&findfiledata))
	{
		if(findfiledata.cFileName[0] == _T('?')) break;
		if(!(findfiledata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
		{
			AString FullName("\\");
			FullName += dir;
			FullName += findfiledata.cFileName;
			FullName.ToUpperCase();
			if(!index->FullIndexes[FullName])
			{
				VdfsIndex::FileInfo* Info = index->Files.Add(new VdfsIndex::FileInfo);
				Info->Flow = this;
				Info->Name = FullName;
				Info->Size = findfiledata.nFileSizeLow;
				index->FullIndexes[Info->Name] = index->Files.Size();

				AString Name(findfiledata.cFileName);
				Name.ToUpperCase();

				if(Name.Compare("A2EE682C.PATCH"))
					printf("!");

				uInt FileIndex = index->FileIndexes[Name];
				if(!FileIndex || (strcmp(Info->Name, index->Files[FileIndex - 1]->Name) < 0))
					index->FileIndexes[Name] = index->Files.Size();

				result++;
			}
		}
		else
		{
			if(_tcscmp(findfiledata.cFileName, _T(".")) && _tcscmp(findfiledata.cFileName, _T("..")))
			{
				TString DirName(dir);
				DirName += findfiledata.cFileName;
				DirName += _T("\\");
				result += BuildIndex(DirName, index);
			}
		}
	}
	if(hf != INVALID_HANDLE_VALUE) FindClose(hf);

	return result;
}

VdfsIndex::FileInfo* StdFlow::GetFileInfo(const AString& filename) 
{
	FILE* file = NULL;
	if(!fopen_s(&file, &filename.GetData()[1], "rb"))
	{
		VdfsIndex::FileInfo* Result = new VdfsIndex::FileInfo;
		Result->Flow = this;
		Result->Name = filename;

		long pos = ftell(file);
		fseek(file, 0, SEEK_END);
		Result->Size = ftell(file);
		fseek(file, 0, SEEK_SET);
		Result->Size -= ftell(file);
		fseek(file, pos, SEEK_SET);

		fclose(file);
		return Result;
	}
	return NULL; 
}

bool StdFlow::FileExists(const AString& filename) 
{
	FILE* file = NULL;
	if(!fopen_s(&file, &filename.GetData()[1], "rb"))
	{
		fclose(file);
		return true;
	}
	return false; 
}

bool StdFlow::UpdateIndex(VdfsIndex* index)
{
	BuildIndex(_T("_work\\"), index);
	Streams.Add(new StdFlow());
	Streams.Add(new StdFlow());
	return true;
}

StdFlow* StdFlow::GetFreeStream(void)
{
	for(uInt i = 0; i < Streams.Size(); i++)
	{
		if(!Streams[i]->CurrentFileInfo)
			return Streams[i];
	}
	return Streams.Add(new StdFlow());
}

IFS* StdFlow::Open(VdfsIndex::FileInfoPtr& fileinfo)
{
	if(fileinfo && (fileinfo->Flow == this))
	{
		StdFlow* Result = GetFreeStream();
		if(Result->Init(fileinfo))
			return Result;
	}
	return NULL;
}

uLong StdFlow::Read(uLong offset, void* buffer, uLong size)
{
	if(FileHandle)
	{
		fseek(FileHandle, offset, SEEK_SET);
		if(fread(buffer, 1, size, FileHandle) == size)
			return size;
	}
	return 0;
}

void StdFlow::Close(void)
{
	if(FileHandle)
	{
		fclose(FileHandle);
		FileHandle = NULL;
	}
	IFS::Close();
}

bool StdFlow::Init(VdfsIndex::FileInfoPtr& fileinfo)
{
	if(FileHandle || CurrentFileInfo)
		return false;

	FILE* file = NULL;
	if(!fopen_s(&file, &fileinfo->Name.GetData()[1], "rb"))
	{
		Name = fileinfo->Name;
		CurrentFileInfo = fileinfo;
		FileHandle = file;
		return true;
	}

	return false;
}