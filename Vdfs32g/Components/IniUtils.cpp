#include "PreCompiled.h"

// Common

bool ReadIniString(const char* section, const char* key, const char* defval, char* val, size_t size, const char* file)
{
	AString SectionString("[");
	SectionString += section;
	SectionString += "]";

	bool InSection = false;
	bool Done = false;

	FILE* In = NULL;
	if(!fopen_s(&In, file, "r"))
	{
		if(In)
		{
			char Line[1024];
			while(fgets(Line, 1024, In))
			{
				if(SectionString.Compare(Line, true, SectionString.Length()))
				{
					InSection = true;
					continue;
				}
				
				if(InSection && strrchr(Line, '='))
				{
					AString Key(Line);
					Key.TruncateAfterFirst("=");
					Key.CleanUp(' ');
					if(Key.Compare(key, true))
					{
						AString Val(Line);
						Val.TruncateBeforeFirst("=");
						Val.TruncateAfterFirst(";");
						Val.CleanUp('\n');

						if(Val.Length())
						{
							strcpy_s(val, size, Val);
							Done = true;
							break;
						}
					}
				}
				else
				if(strrchr(Line, '['))
					InSection = false;
			}
		}

		fclose(In);
	}
	if(!Done)
		strcpy_s(val, size, defval);
	return Done;
}

bool WriteIniString(const char* section, const char* key, const char* val, const char* file)
{
	AString BakFile(file);
	BakFile += ".bak";

	AString SectionString("[");
	SectionString += section;
	SectionString += "]";

	AString ValString(key);
	ValString += "=";
	ValString += val;

	FILE* In = NULL;
	if(PathFileExistsA(file))
	{
		DeleteFileA(BakFile);
		if(!MoveFileA(file, BakFile))
			return false;
		if(fopen_s(&In, BakFile, "r"))
			return false;
	}

	bool SectionDone = false;
	bool Done = false;

	FILE* Out = NULL;
	if(!fopen_s(&Out, file, "w"))
	{
		if(In)
		{
			char Line[1024];
			while(fgets(Line, 1024, In))
			{
				bool SkipLine = false;

				if(!SectionDone)
				{
					if(SectionString.Compare(Line, true, SectionString.Length()))
						SectionDone = true;
				}
				else
				{
					if(!Done)
					{
						if(strrchr(Line, '='))
						{
							AString Key(Line);
							Key.TruncateAfterFirst("=");
							Key.CleanUp(' ');
							if(Key.Compare(key, true))
							{
								Done = true;
								fprintf(Out, "%s\n", ValString.GetData());
								SkipLine = true;
							}
						}
						else
						if(strrchr(Line, '['))
						{
							Done = true;
							fprintf(Out, "%s\n", ValString.GetData());
						}
					}
				}
				if(!SkipLine)
				{
					if(Line[strlen(Line) - 1] == '\n')
						fprintf(Out, "%s", Line);
					else
						fprintf(Out, "%s\n", Line);
				}
			}
		}

		if(!SectionDone)
		{
			SectionDone = true;
			Done = true;

			fprintf(Out, "%s\n", SectionString.GetData());
			fprintf(Out, "%s\n", ValString.GetData());
		}
		else
		if(!Done)
		{
			Done = true;
			fprintf(Out, "%s\n", ValString.GetData());
		}
		fclose(Out);
	}

	if(In)
	{
		fclose(In);
		DeleteFileA(BakFile);
	}
	return SectionDone && Done;
}

// Utility

bool GothicReadIniString(const char* section, const char* key, const char* defval, char* val, size_t size, const char* file)
{
	TString WorkPath;
	if(PlatformGetWorkPath(WorkPath) && WorkPath.TruncateBeforeLast(_T("\\")))
	{
		AString File("SystemPack.ini");
		if(!_stricmp(file, "SystemPack.ini"))
		{
			if(!WorkPath.Compare(_T("System"), true))
				File.Assign("System\\SystemPack.ini");

			char Buffer[256];
			ReadIniString("SYSTEM", "RedirectToGothicIni", "0", Buffer, 256, File);

			if((atoi(Buffer) != 0))
				file = "Gothic.ini";
		}

		File.Assign(file);
		if(!WorkPath.Compare(_T("System"), true))
			File.Format("System\\%s", file);

		return ReadIniString(section, key, defval, val, size, File);
	}
	return false;
}

bool GothicWriteIniString(const char* section, const char* key, const char* val, const char* file)
{
	TString WorkPath;
	if(PlatformGetWorkPath(WorkPath) && WorkPath.TruncateBeforeLast(_T("\\")))
	{
		AString File("SystemPack.ini");
		if(!_stricmp(file, "SystemPack.ini"))
		{
			if(!WorkPath.Compare(_T("System"), true))
				File.Assign("System\\SystemPack.ini");

			char Buffer[256];
			ReadIniString("SYSTEM", "RedirectToGothicIni", "0", Buffer, 256, File);

			if((atoi(Buffer) != 0))
				file = "Gothic.ini";
		}

		File.Assign(file);
		if(!WorkPath.Compare(_T("System"), true))
			File.Format("System\\%s", file);

		return WriteIniString(section, key, val, File);
	}
	return false;
}