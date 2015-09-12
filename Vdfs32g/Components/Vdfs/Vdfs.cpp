#include "PreCompiled.h"

long Vdfs::FileExist(const char* filename, long flags)
{
	if(flags & VDF_PACKED)
		MessageBox(NULL, _T("vdf_fexists unsupported flag VDF_PACKED"), _T("VDFS"), MB_ICONERROR);
	if(flags & VDF_NOBUFFER)
		MessageBox(NULL, _T("vdf_fexists unsupported flag VDF_NOBUFFER"), _T("VDFS"), MB_ICONERROR);

	EnterCriticalSection(&CS);
	if((flags & VDF_PHYSICALFIRST) && (flags & VDF_PHYSICAL))
	{
		if(PhysicalFlow->FileExists(filename))
		{
			LeaveCriticalSection(&CS);
			return VDF_PHYSICAL;
		}
	}
	if(flags & VDF_VIRTUAL)
	{
		VdfsIndex::FileInfo* FileInfo = Index->GetFileInfo(filename);
		if(FileInfo)
		{
			long Result = (FileInfo->Flow == PhysicalFlow) ? VDF_PHYSICAL : VDF_VIRTUAL;
			LeaveCriticalSection(&CS);
			return Result;
		}
	}
	if((!(flags & VDF_PHYSICALFIRST)) && (flags & VDF_PHYSICAL))
	{
		if(PhysicalFlow->FileExists(filename))
		{
			LeaveCriticalSection(&CS);
			return VDF_PHYSICAL;
		}
	}
	LeaveCriticalSection(&CS);
	return 0;
}

bool Vdfs::SearchFile(const char* filename, char* fullname)
{
	EnterCriticalSection(&CS);
	String UpperName(filename);
	UpperName.ToUpperCase();
	bool Result = Index->SearchFile(UpperName, fullname);
	//printf("%s -> %s\n", filename, fullname);
	LeaveCriticalSection(&CS);
	return Result;
}

IfsBase* Vdfs::ApplyFilter(IFS* src)
{
	for(uInt f = 0; src && (f < Filters.Size()); f++)
	{
		IfsBase* Res = Filters[f]->Open(src);
		if(Res)
			return Res;
	}
	return src;
}

IfsBase* Vdfs::OpenFile(const char* filename, long flags)
{
	if(flags & VDF_PACKED)
		MessageBox(NULL, _T("vdf_fopen unsupported flag VDF_PACKED"), _T("VDFS"), MB_ICONERROR);
	if(flags & VDF_NOBUFFER)
		MessageBox(NULL, _T("vdf_fopen unsupported flag VDF_NOBUFFER"), _T("VDFS"), MB_ICONERROR);

	EnterCriticalSection(&CS);
	
	if((flags & VDF_PHYSICALFIRST) && (flags & VDF_PHYSICAL))
	{
		VdfsIndex::FileInfoPtr FileInfo = PhysicalFlow->GetFileInfo(filename);
		if(FileInfo)
		{
			IFS* Result = FileInfo->Flow->Open(FileInfo);
			LeaveCriticalSection(&CS);
			return ApplyFilter(Result);
		}
	}
	if(flags & VDF_VIRTUAL)
	{
		VdfsIndex::FileInfoPtr FileInfo = Index->GetFileInfo(filename);
		if(FileInfo)
		{
			FileInfo.SetAuto(false); // In index file infos are created not by new
			IFS* Result = FileInfo->Flow->Open(FileInfo);
			LeaveCriticalSection(&CS);
			return ApplyFilter(Result);
		}
	}
	if((!(flags & VDF_PHYSICALFIRST)) && (flags & VDF_PHYSICAL))
	{
		VdfsIndex::FileInfoPtr FileInfo = PhysicalFlow->GetFileInfo(filename);
		if(FileInfo)
		{
			IFS* Result = FileInfo->Flow->Open(FileInfo);
			LeaveCriticalSection(&CS);
			return ApplyFilter(Result);
		}
	}
	LeaveCriticalSection(&CS);
	return NULL;
}

void Vdfs::CloseFile(IfsBase* fp)
{
	EnterCriticalSection(&CS);
	if(fp)
		fp->Close();
	LeaveCriticalSection(&CS);
}

int VdfCompTimeStamp(const IfsPtr& Obj1, const IfsPtr& Obj2, Object* arg)
{
	if((Obj1->GetType() == IFS_TYPE_VDF) && (Obj2->GetType() == IFS_TYPE_VDF))
	{
		VdfTime Time1 = dcast<const VdfFlow*>((const IFS*)Obj1)->GetTimeStamp();
		VdfTime Time2 = dcast<const VdfFlow*>((const IFS*)Obj2)->GetTimeStamp();
		if(*(uInt*)&Time1 == *(uInt*)&Time2) return 0;
		if(*(uInt*)&Time1 < *(uInt*)&Time2) return 1;
		return -1;
	}
	return 0;
}

void Vdfs::EnumDirs(const TCHAR* dir, TStringArray& dirs, bool recurse)
{
	TString SearchString(dir);
	SearchString += _T("*");

	WIN32_FIND_DATA findfiledata;
	findfiledata.cFileName[0] = _T('?');
	HANDLE hf = FindFirstFile(SearchString, &findfiledata);
	for(BOOL cont = true; (hf != INVALID_HANDLE_VALUE) && (cont != false); cont = FindNextFile(hf, (LPWIN32_FIND_DATA)&findfiledata))
	{
		if(findfiledata.cFileName[0] == _T('?')) break;
		if(findfiledata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if(_tcscmp(findfiledata.cFileName, _T(".")) && _tcscmp(findfiledata.cFileName, _T("..")))
			{
				TString& DirName = dirs.Add();
				DirName = dir;
				DirName += findfiledata.cFileName;
				DirName += _T("\\");
				if(recurse)
					EnumDirs(DirName, dirs, recurse);
			}
		}
	}
	if(hf != INVALID_HANDLE_VALUE) FindClose(hf);
}

void Vdfs::MountDir(const TCHAR* dir, const TCHAR* ext)
{
	TStringArray Dirs;
	Dirs.Add(dir);
	//EnumDirs(dir, Dirs, false);

	for(uInt i = 0; i < Dirs.Size(); i++)
	{
		TString SearchString(Dirs[i]);
		SearchString += ext;

		WIN32_FIND_DATA findfiledata;
		findfiledata.cFileName[0] = _T('?');
		HANDLE hf = FindFirstFile(SearchString, &findfiledata);
		for(BOOL cont = true; (hf != INVALID_HANDLE_VALUE) && (cont != false); cont = FindNextFile(hf, (LPWIN32_FIND_DATA)&findfiledata))
		{
			if(findfiledata.cFileName[0] == _T('?')) break;
			if(!(findfiledata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				TString ArcName(Dirs[i]);
				ArcName += findfiledata.cFileName;
				VdfFlowPtr Flow = new VdfFlow;
				if(Flow->Init(ArcName))
					VirtualFlows.Add(Flow);
			}
		}
		if(hf != INVALID_HANDLE_VALUE) FindClose(hf);
	}
}

bool Vdfs::UpdateStdFileIndex(const AString& file, uInt size)
{
	if(PhysicalFlow && Index)
		return dcast<StdFlow*>(PhysicalFlow)->UpdateFileIndex(file, size, false, Index);
	return true;
}

bool Vdfs::InitVirtual(void)
{
	EnterCriticalSection(&CS);

	if(!VirtualFlows.Size())
	{
		MountDir(_T("Data\\"), _T("*.vdf"));
		MountDir(_T("Data\\"), _T("*.mod"));

		if(VirtualFlows.Size() > 2)
		{
			VirtualFlows.SetComparator(VdfCompTimeStamp);
			VirtualFlows.SortSubSet(0, VirtualFlows.Size() - 1);
		}
		PhysicalFlow = new StdFlow();

		Index = new VdfsIndex();
		for(uInt i = 0; i < VirtualFlows.Size(); i++)
			VirtualFlows[i]->UpdateIndex(Index);
	}

	LeaveCriticalSection(&CS);
	return true;
}

bool Vdfs::Init(void)
{
	EnterCriticalSection(&CS);

	Filters.Add(new OggFilter);

	if(!Index)
		InitVirtual();
	PhysicalFlow->UpdateIndex(Index);

	LeaveCriticalSection(&CS);
	return true;
}

void Vdfs::Clear(void)
{
	EnterCriticalSection(&CS);
	PhysicalFlow = NULL;
	VirtualFlows.Clear();
	LeaveCriticalSection(&CS);
}

Vdfs::Vdfs(void) 
{ 
	InitializeCriticalSection(&CS); 
	PhysicalFlow = NULL; 
}

Vdfs::~Vdfs(void) 
{
	Clear();
	DeleteCriticalSection(&CS);
}