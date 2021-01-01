#include "PreCompiled.h"
#include <string>
#include <filesystem>

BOOL
WINAPI
MyDeleteFileA(
	__in LPCSTR lpFileName
)
{
	const char* savegame = "savegame";
	if(!strncmp(lpFileName, savegame, sizeof(savegame)))
	{
		std::string savegameBak("bak_");
		savegameBak += lpFileName;

		std::string savegameBakDir(savegameBak);
		savegameBakDir.erase(savegameBakDir.find("\\"));
		std::filesystem::create_directories(savegameBakDir);

		DeleteFileA(savegameBak.c_str());
		return MoveFileA(lpFileName, savegameBak.c_str());
	}
	return DeleteFileA(lpFileName);
}

bool InstallSaveBakFix(void)
{
	uChar* codeBase = (uChar*)GetModuleHandle(NULL);
	PIMAGE_IMPORT_DESCRIPTOR importDesc = GetImportDescriptor(codeBase, "KERNEL32.dll");
	if(importDesc)
		PatchImportFunctionAddress<FARPROC>(codeBase, importDesc, false, "DeleteFileA", (FARPROC)MyDeleteFileA);
	return true;
}

void RemoveSaveBakFix(void)
{
}