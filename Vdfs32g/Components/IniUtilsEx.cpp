#include "PreCompiled.h"

uInt ReadIniSections(AStringArray& sections, const TCHAR* file)
{
	if(!file)
		return 0;
	FILE* In = NULL;
	if(!_tfopen_s(&In, file, _T("r")))
	{
		if(In)
		{
			char Line[1024];
			while(fgets(Line, 1024, In))
			{
				if(strstr(Line, "[") && strstr(Line, "]"))
				{
					AString Section(Line);
					Section.TruncateAfterFirst(";");
					Section.SetCompareIgnoreCase(true);
					if(Section.TruncateBeforeFirst("[") && Section.TruncateAfterFirst("]") && Section.Length())
						sections.Add(Section);
				}
			}
		}

		fclose(In);
	}
	return sections.Size();
}

bool MyReadLine(FILE* In, AString& line)
{
	line.Clear();
	char Line[256];
	while(fgets(Line, 256, In))
	{
		line.Append(Line);
		if((line[line.Length() - 1] == '\n'))
			return true;
		if(feof(In))
			return true;
	}
	return false;
}

uInt ReadIniSectionParams(TaggedArray<AString, AString>& params, const char* section, const TCHAR* file)
{
	AString SectionString("[");
	SectionString += section;
	SectionString += "]";

	bool InSection = false;

	FILE* In = NULL;
	if(!_tfopen_s(&In, file, _T("r")))
	{
		if(In)
		{
			AString Readed;
			while(MyReadLine(In, Readed))
			{
				if(SectionString.Compare(Readed, true, SectionString.Length()))
				{
					InSection = true;
					continue;
				}
				
				if(InSection && strrchr(Readed, '='))
				{
					AString Key(Readed);
					Key.TruncateAfterFirst(";");
					Key.TruncateAfterFirst("=");
					Key.CleanUp(' ');
					if((Key.FirstCharNotInSet(" \t") != NULL) && Key.Length())
					{
						AString Val(Readed);
						Val.TruncateAfterFirst(";");
						Val.TruncateBeforeFirst("=");
						Val.CleanUp('\n');
						Val.Assign(Val.FirstCharNotInSet(" \t"));

						if(Val.Length())
						{
							Key.SetCompareIgnoreCase(true);
							params.Add(Key, Val);
						}
					}
				}
				else
				if(strrchr(Readed, '['))
					InSection = false;
			}
		}

		fclose(In);
	}
	return params.Size();
}