#include "PreCompiled.h"

TaggedArray<uChar*, AString> MemoryBlocks;

bool PatchPtr(AString& section, TaggedArray<AString, AString>& params)
{
	bool CheckOrg = false;
	uInt Org = 0;
	uInt New = 0;

	AString& OrgText = params.GetElement("Org");
	AString& OrgOffsetText = params.GetElement("OrgOffset");
	CheckOrg = (((OrgText.Length() > 0) && OrgText.IsUInt()) || ((OrgOffsetText.Length() > 0) && OrgOffsetText.IsUInt()));
	Org = (uInt)OrgText.ToUInt();
	Org += OrgOffsetText.ToUInt();

	New = (uInt)MemoryBlocks.GetElement(params.GetElement("NewBlock"));
	New += (uInt)params.GetElement("NewOffset").ToUInt();

	AString& AddrSectText = params.GetElement("AddrSect");
	if(AddrSectText.Length())
	{
		size_t size = 0;
		const uChar* data = GetSectionAddress((const uChar*)GetModuleHandle(NULL), AddrSectText, size);
		if(!data)
			return false;
		for(size_t i = 0; i < size; i++)
		{
			if(*(uInt*)&data[i] == Org)
			{
				if(!Patch((uChar*)&data[i], sizeof(void*), CheckOrg ? (uChar*)&Org : NULL, (uChar*)&New))
				{
					RedirectIOToConsole();
					printf("%s failed\n", section.GetData());
					return false;
				}
			}
		}
	}
	else
	{
		uChar* Address = NULL;

		AString& AddrText = params.GetElement("Addr");
		Address = (uChar*)AddrText.ToUInt();

		AString& BaseText = params.GetElement("Base");
		if(BaseText)
			Address = (uChar*)((uInt)Address + (uInt)MemoryBlocks.GetElement(BaseText));

		if(!Patch(Address, sizeof(void*), CheckOrg ? (uChar*)&Org : NULL, (uChar*)&New))
		{
			RedirectIOToConsole();
			printf("%s failed\n", section.GetData());
			return false;
		}
	}

	return true;
}

bool PatchInt(AString& section, TaggedArray<AString, AString>& params)
{
	bool CheckOrg = false;
	int Org = 0;
	int New = 0;

	AString& OrgText = params.GetElement("Org");
	CheckOrg = ((OrgText.Length() > 0) && OrgText.IsInt());
	Org = OrgText.ToInt();

	AString& NewText = params.GetElement("New");
	if(NewText.Length() && NewText.IsInt())
		New = NewText.ToInt();

	AString& NewVarText = params.GetElement("NewVar");
	if(NewVarText.Length() && NewVarText.GetData(":"))
	{
		AString NewVarSect(NewVarText);
		AString NewVarParam(NewVarText);
		if(NewVarSect.TruncateAfterFirst(":") && NewVarParam.TruncateBeforeFirst(":"))
		{
			char Value[256];
			if(GothicReadIniString(NewVarSect, NewVarParam, "", Value, 256, "SystemPack.ini"))
				New += atoi(Value);
		}
	}

	AString& NewMulText = params.GetElement("NewMul");
	if(NewMulText.Length() && NewMulText.IsInt())
		New *= NewMulText.ToInt();

	AString& NewAddText = params.GetElement("NewAdd");
	if(NewAddText.Length() && NewAddText.IsInt())
		New += NewAddText.ToInt();

	AString& NewMinText = params.GetElement("NewMin");
	if(NewMinText.Length() && NewMinText.IsInt())
	{
		int NewMin = NewMinText.ToInt();
		if(New < NewMin)
			New = NewMin;
	}

	AString& NewMaxText = params.GetElement("NewMax");
	if(NewMaxText.Length() && NewMaxText.IsInt())
	{
		int NewMax = NewMaxText.ToInt();
		if(New > NewMax)
			New = NewMax;
	}

	AString& AddrSectText = params.GetElement("AddrSect");
	if(AddrSectText.Length())
	{
		size_t size = 0;
		const uChar* data = GetSectionAddress((const uChar*)GetModuleHandle(NULL), AddrSectText, size);
		for(size_t i = 0; i < size; i++)
		{
			if(*(int*)&data[i] == Org)
			{
				if(!Patch((uChar*)&data[i], sizeof(int), CheckOrg ? (uChar*)&Org : NULL, (uChar*)&New))
				{
					RedirectIOToConsole();
					printf("%s failed\n", section.GetData());
					return false;
				}
			}
		}
	}
	else
	{
		uChar* Address = NULL;

		AString& AddrText = params.GetElement("Addr");
		Address = (uChar*)AddrText.ToUInt();

		AString& BaseText = params.GetElement("Base");
		if(BaseText)
			Address = (uChar*)((uInt)Address + (uInt)MemoryBlocks.GetElement(BaseText));

		if(!Patch(Address, sizeof(int), CheckOrg ? (uChar*)&Org : NULL, (uChar*)&New))
		{
			RedirectIOToConsole();
			printf("%s failed\n", section.GetData());
			return false;
		}
	}

	return true;
}

bool PatchFloat(AString& section, TaggedArray<AString, AString>& params)
{
	bool CheckOrg = false;
	float Org = 0.0f;
	float New = 0.0f;

	AString& OrgText = params.GetElement("Org");
	CheckOrg = ((OrgText.Length() > 0) && OrgText.IsFloat());
	Org = OrgText.ToFloat();

	AString& NewText = params.GetElement("New");
	if(NewText.Length() && NewText.IsFloat())
		New = NewText.ToFloat();

	AString& NewVarText = params.GetElement("NewVar");
	if(NewVarText.Length() && NewVarText.GetData(":"))
	{
		AString NewVarSect(NewVarText);
		AString NewVarParam(NewVarText);
		if(NewVarSect.TruncateAfterFirst(":") && NewVarParam.TruncateBeforeFirst(":"))
		{
			char Value[256];
			if(GothicReadIniString(NewVarSect, NewVarParam, "", Value, 256, "SystemPack.ini"))
				New += (float)atof(Value);
		}
	}

	AString& NewMulText = params.GetElement("NewMul");
	if(NewMulText.Length() && NewMulText.IsFloat())
		New *= NewMulText.ToFloat();

	AString& NewAddText = params.GetElement("NewAdd");
	if(NewAddText.Length() && NewAddText.IsFloat())
		New += NewAddText.ToFloat();

	AString& NewMinText = params.GetElement("NewMin");
	if(NewMinText.Length() && NewMinText.IsFloat())
	{
		float NewMin = NewMinText.ToFloat();
		if(New < NewMin)
			New = NewMin;
	}

	AString& NewMaxText = params.GetElement("NewMax");
	if(NewMaxText.Length() && NewMaxText.IsFloat())
	{
		float NewMax = NewMaxText.ToFloat();
		if(New > NewMax)
			New = NewMax;
	}

	AString& AddrSectText = params.GetElement("AddrSect");
	if(AddrSectText.Length())
	{
		size_t size = 0;
		const uChar* data = GetSectionAddress((const uChar*)GetModuleHandle(NULL), AddrSectText, size);
		for(size_t i = 0; i < size; i++)
		{
			if(*(float*)&data[i] == Org)
			{
				if(!Patch((uChar*)&data[i], sizeof(float), CheckOrg ? (uChar*)&Org : NULL, (uChar*)&New))
				{
					RedirectIOToConsole();
					printf("%s failed\n", section.GetData());
					return false;
				}
			}
		}
	}
	else
	{
		uChar* Address = NULL;

		AString& AddrText = params.GetElement("Addr");
		Address = (uChar*)AddrText.ToUInt();

		AString& BaseText = params.GetElement("Base");
		if(BaseText)
			Address = (uChar*)((uInt)Address + (uInt)MemoryBlocks.GetElement(BaseText));

		if(!Patch(Address, sizeof(float), CheckOrg ? (uChar*)&Org : NULL, (uChar*)&New))
		{
			RedirectIOToConsole();
			printf("%s failed\n", section.GetData());
			return false;
		}
	}

	return true;
}

bool PatchHex(AString& section, TaggedArray<AString, AString>& params)
{
	Array<uChar> Org;
	Array<uChar> New;

	AString& NewText = params.GetElement("New");
	NewText.CleanUp(' ');
	NewText.CleanUp('\t');
	for(uInt n = 0; n < NewText.Length() / 2; n++)
	{
		uInt Value = 0;
		char Buffer[3] = { NewText[n * 2], NewText[n * 2 + 1], '\0' };
		sscanf(Buffer, "%x", &Value);
		New.Add((uChar)Value);
	}

	if(!NewText.Length())
	{
		AString& NewAnsi = params.GetElement("NewAnsi");
		if(NewAnsi)
			New.Add((const uChar*)NewAnsi.GetData(), NewAnsi.Length() + 1);
	}

	AString& OrgText = params.GetElement("Org");
	if(OrgText)
	{
		OrgText.CleanUp(' ');
		OrgText.CleanUp('\t');
		for(uInt n = 0; n < OrgText.Length() / 2; n++)
		{
			uInt Value = 0;
			char Buffer[3] = { OrgText[n * 2], OrgText[n * 2 + 1], '\0' };
			sscanf(Buffer, "%x", &Value);
			Org.Add((uChar)Value);
		}
	}
	else
	{
		Array<uChar> OrgFill;

		AString& OrgFillText = params.GetElement("OrgFill");
		OrgFillText.CleanUp(' ');
		OrgFillText.CleanUp('\t');
		for(uInt n = 0; n < OrgFillText.Length() / 2; n++)
		{
			uInt Value = 0;
			char Buffer[3] = { OrgFillText[n * 2], OrgFillText[n * 2 + 1], '\0' };
			sscanf(Buffer, "%x", &Value);
			OrgFill.Add((uChar)Value);
		}

		if(OrgFill.Size())
		{
			while(Org.Size() < New.Size())
				Org.Add(OrgFill);
			Org.SetSize(New.Size());
		}
	}

	if((New.Size() != Org.Size()) && Org.Size())
	{
		RedirectIOToConsole();
		printf("%s failed, New.Size() != Org.Size()\n", section.GetData());
		return false;
	}

	AString& AddrSectText = params.GetElement("AddrSect");
	if(AddrSectText.Length())
		return false;
	else
	{
		uChar* Address = NULL;

		AString& AddrText = params.GetElement("Addr");
		Address = (uChar*)AddrText.ToUInt();

		AString& BaseText = params.GetElement("Base");
		if(BaseText)
			Address = (uChar*)((uInt)Address + (uInt)MemoryBlocks.GetElement(BaseText));

		if(!Patch(Address, New.Size(), Org.Size() ? Org : NULL, New))
		{
			RedirectIOToConsole();
			printf("%s failed\n", section.GetData());
			return false;
		}
	}

	return true;
}

bool ApplyPatch(const TString& filename)
{
	AStringArray Sections;
	if(ReadIniSections(Sections, filename))
	{
		// ConVars
		TaggedArray<AString, AString> ConVars;
		if(ReadIniSectionParams(ConVars, "ConVars", filename))
		{
			for(uInt v = 0; v < ConVars.Size(); v++)
			{
				ConVars.GetElement(v).TruncateBeforeFirst("\"");
				ConVars.GetElement(v).TruncateAfterFirst("\"");

				AString ConVarSect(ConVars.GetTag(v));
				AString ConVar(ConVars.GetTag(v));
				if(ConVarSect.TruncateAfterFirst(":") && ConVar.TruncateBeforeFirst(":"))
				{
					char Value[256];
					if(!GothicReadIniString(ConVarSect, ConVar, ConVars.GetElement(v), Value, 256, "SystemPack.ini"))
					{
						if(ConVars.GetElement(v).GetData(":"))
						{
							AString ValueConVarSect(ConVars.GetElement(v));
							AString ValueConVar(ConVars.GetElement(v));
							if(!ValueConVarSect.TruncateAfterFirst(":") || !ValueConVar.TruncateBeforeFirst(":") || !GothicReadIniString(ValueConVarSect, ValueConVar, "", Value, 256, "SystemPack.ini"))
							{
								RedirectIOToConsole();
								printf("%s failed\n", ConVars.GetTag(v).GetData());
								return false;
							}
						}
						GothicWriteIniString(ConVarSect, ConVar, Value, "SystemPack.ini");
					}
				}
			}
		}
		Sections.Erase(_T("ConVars"));

		// MemBlocks
		TaggedArray<AString, AString> MemBlocks;
		if(ReadIniSectionParams(MemBlocks, "MemBlocks", filename))
		{
			for(uInt b = 0; b < MemBlocks.Size(); b++)
			{
				MemBlocks.GetElement(b).TruncateBeforeFirst("\"");
				MemBlocks.GetElement(b).TruncateAfterFirst("\"");

				if(MemBlocks.GetElement(b).IsUInt())
					MemoryBlocks.Add(MemBlocks.GetTag(b), (uChar*)VirtualAlloc(NULL, (SIZE_T)MemBlocks.GetElement(b).ToUInt(), MEM_COMMIT | MEM_RESERVE, MemBlocks.GetTag(b).Compare("Exe", true, 3) ? PAGE_EXECUTE_READWRITE : PAGE_READWRITE));
			}
		}
		Sections.Erase(_T("MemBlocks"));

		// Patches
		for(uInt s = 0; s < Sections.Size(); s++)
		{
			TaggedArray<AString, AString> Params;
			if(ReadIniSectionParams(Params, Sections.GetElement(s), filename))
			{
				for(uInt p = 0; p < Params.Size(); p++)
				{
					Params.GetElement(p).TruncateBeforeFirst("\"");
					Params.GetElement(p).TruncateAfterFirst("\"");
				}

				AString& Condition = Params.GetElement("Condition");
				if(Condition)
				{
					bool Skip = true;

					AString ConditionSect(Condition);
					AString ConditionParam(Condition);
					if(!ConditionSect.TruncateAfterFirst(":") || !ConditionParam.TruncateBeforeFirst(":"))
						continue;
					char Value[256];
					if(!GothicReadIniString(ConditionSect, ConditionParam, "", Value, 256, "SystemPack.ini"))
						continue;

					AStringArrayPtr ConditionValues = Params.GetElement("ConditionValue").GetAllTokens(",");
					if(ConditionValues)
					{
						for(uInt v = 0; v < ConditionValues->Size(); v++)
						{
							if(!(Skip = !ConditionValues->GetElement(v).Compare(Value, true)))
								break;
						}
					}
					else
					{
						AStringArrayPtr ConditionNotValues = Params.GetElement("ConditionNotValue").GetAllTokens(",");
						if(ConditionNotValues)
						{
							for(uInt v = 0; v < ConditionNotValues->Size(); v++)
							{
								if(!(Skip = ConditionNotValues->GetElement(v).Compare(Value, true)))
									break;
							}
						}
					}
					if(Skip)
						continue;
				}

				AString& Type = Params.GetElement("Type");
				if(Type.Compare("ptr", true))
				{
					if(!PatchPtr(Sections.GetElement(s), Params))
						return false;
				}
				else
				if(Type.Compare("int", true))
				{
					if(!PatchInt(Sections.GetElement(s), Params))
						return false;
				}
				else
				if(Type.Compare("float", true))
				{
					if(!PatchFloat(Sections.GetElement(s), Params))
						return false;
				}
				else
				if(Type.Compare("hex", true))
				{
					if(!PatchHex(Sections.GetElement(s), Params))
						return false;
				}
			}
		}
	}
	return true;
}

typedef enum PROCESS_DPI_AWARENESS {
    PROCESS_DPI_UNAWARE = 0,
    PROCESS_SYSTEM_DPI_AWARE = 1,
    PROCESS_PER_MONITOR_DPI_AWARE = 2
} PROCESS_DPI_AWARENESS;

typedef HRESULT (STDAPICALLTYPE* SetProcessDpiAwarenessPtr)(PROCESS_DPI_AWARENESS value);
typedef HRESULT (STDAPICALLTYPE* GetProcessDpiAwarenessPtr)(HANDLE hprocess, PROCESS_DPI_AWARENESS *value);

HRESULT SetProcessDpiAwareness(PROCESS_DPI_AWARENESS value)
{
	HRESULT hResult = S_FALSE;
	HMODULE hModule = LoadLibrary(_T("Shcore.dll"));
	if(hModule)
	{
		SetProcessDpiAwarenessPtr Func = (SetProcessDpiAwarenessPtr)GetProcAddress(hModule, "SetProcessDpiAwareness");
		if(Func)
			hResult = Func(value);
		FreeLibrary(hModule);
	}
	return hResult; 
}

HRESULT GetProcessDpiAwareness(HANDLE hprocess, PROCESS_DPI_AWARENESS* value)
{
	HRESULT hResult = S_FALSE;
	HMODULE hModule = LoadLibrary(_T("Shcore.dll"));
	if(hModule)
	{
		GetProcessDpiAwarenessPtr Func = (GetProcessDpiAwarenessPtr)GetProcAddress(hModule, "GetProcessDpiAwareness");
		if(Func)
			hResult = Func(hprocess, value);
		FreeLibrary(hModule);
	}
	return hResult; 
}

typedef BOOL (WINAPI* SetProcessDPIAwarePtr)(VOID);

BOOL SafeSetProcessDPIAware(VOID)
{
	BOOL hResult = FALSE;
	HMODULE hModule = LoadLibrary(_T("user32.dll"));
	if(hModule)
	{
		SetProcessDPIAwarePtr Func = (SetProcessDPIAwarePtr)GetProcAddress(hModule, "SetProcessDPIAware");
		if(Func)
			hResult = Func();
		FreeLibrary(hModule);
	}
	return hResult; 
}

uLong ExeCRC = 0;
uLong CodeCRC = 0;

bool PreInstallKillerFix(void)
{
	if(IsWindows8Point1OrGreater())
	{
		if(SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE) != S_OK)
		{
			RedirectIOToConsole();
			printf("Failed to set process DPI awareness\n");
		}
	}
	else
	if(IsWindows7OrGreater())
	{
		if(!SafeSetProcessDPIAware())
		{
			RedirectIOToConsole();
			printf("Failed to set process DPI aware\n");
		}
	}

	bool Result = false;
	TString TempFile;

	bool ChangeWorkDir = false;
	TString WorkPath;
	if(PlatformGetWorkPath(WorkPath) && WorkPath.TruncateBeforeLast(_T("\\")) && WorkPath.Compare(_T("System"), true))
		ChangeWorkDir = (SetCurrentDirectory(_T("..\\")) == TRUE);

	ExeCRC = GetExeCrc32();
	CodeCRC = GetSectionCrc32(".text");
	if(PathFileExists(TempFile.Format(_T("Patches\\PRE_%X.patch"), ExeCRC)) || PathFileExists(TempFile.Format(_T("Patches\\CODE_PRE_%X.patch"), CodeCRC)))
	{
		Result = true;
	}
	else
	if(!vdf_initall_internal())
	{	
		char PatchFileName[256];
		PatchFileName[0] = '\\';
		if(vdf_searchfile(String().Format("PRE_%X.PATCH", ExeCRC), &PatchFileName[1]) || vdf_searchfile(String().Format("CODE_PRE_%X.PATCH", CodeCRC), &PatchFileName[1]))
		{
			long patch = vdf_fopen(PatchFileName, VDF_VIRTUAL);
			if(patch > 0)
			{
				if(vdf_ffilesize(patch) && PlatformGetTempFileName(TempFile))
				{
					FILE* temp = _tfopen(TempFile, _T("wb"));
					if(temp)
					{
						char Buffer[256];
						long readed = 0;
						while(readed = vdf_fread(patch, Buffer, 256))
							fwrite(Buffer, 1, readed, temp);
						Result = true;
						fclose(temp);
					}
				}
				vdf_fclose(patch);
			}
		}
	}

	if(Result)
		Result = ApplyPatch(TempFile);
	else
	{
		char UnknExeCrc[256];
		if(!GothicReadIniString("DEBUG", "UnknExeCrc", "0", UnknExeCrc, 256, "SystemPack.ini") || (strtoul(UnknExeCrc, NULL, 16) != ExeCRC))
		{
			TCHAR Buffer[256];
			_stprintf_s(Buffer, 256, _T("Unsupported gothic exe version (CRC: 0x%X, CodeCRC: 0x%X), fix will not be applied"), ExeCRC, CodeCRC);
			if(MessageBox(NULL, Buffer, _T("Warning"), MB_ICONWARNING | MB_OKCANCEL) != IDOK)
				return false;
			Result = true;

			sprintf_s(UnknExeCrc, 256, "0x%X", ExeCRC);
			GothicWriteIniString("DEBUG", "UnknExeCrc", UnknExeCrc, "SystemPack.ini");
		}
		else
			Result = true;
	}

	if(ChangeWorkDir)
		SetCurrentDirectory(_T("System\\"));
	return Result;
}

bool InstallKillerFix(void)
{
	GothicWriteIniString("SYSTEM", "NvidiaVga", HasVgaVendor(0x10DE) ? "1" : "0", "SystemPack.ini");

	bool Result = false;
	TString TempFile;

	bool ChangeWorkDir = false;
	TString WorkPath;
	if(PlatformGetWorkPath(WorkPath) && WorkPath.TruncateBeforeLast(_T("\\")) && WorkPath.Compare(_T("System"), true))
		ChangeWorkDir = (SetCurrentDirectory(_T("..\\")) == TRUE);

	if(PathFileExists(TempFile.Format(_T("Patches\\POST_%X.patch"), ExeCRC)) || PathFileExists(TempFile.Format(_T("Patches\\CODE_POST_%X.patch"), CodeCRC)))
	{
		Result = true;
	}
	else
	if(!vdf_initall_internal())
	{	
		char PatchFileName[256];
		PatchFileName[0] = '\\';
		if(vdf_searchfile(String().Format("POST_%X.PATCH", ExeCRC), &PatchFileName[1]) || vdf_searchfile(String().Format("CODE_POST_%X.PATCH", CodeCRC), &PatchFileName[1]))
		{
			long patch = vdf_fopen(PatchFileName, VDF_VIRTUAL);
			if(patch > 0)
			{
				if(vdf_ffilesize(patch) && PlatformGetTempFileName(TempFile))
				{
					FILE* temp = _tfopen(TempFile, _T("wb"));
					if(temp)
					{
						char Buffer[256];
						long readed = 0;
						while(readed = vdf_fread(patch, Buffer, 256))
							fwrite(Buffer, 1, readed, temp);
						Result = true;
						fclose(temp);
					}
				}
				vdf_fclose(patch);
			}
		}
	}

	if(Result)
		Result = ApplyPatch(TempFile);

	if(ChangeWorkDir)
		SetCurrentDirectory(_T("System\\"));
	return Result;
}

void RemoveKillerFix(void)
{
	for(uInt b = 0; b < MemoryBlocks.Size(); b++)
	{
		if(MemoryBlocks[b])
			VirtualFree(MemoryBlocks[b], 0, MEM_RELEASE);
	}
	MemoryBlocks.Clear();
}