#include "PreCompiled.h"

bool zTexCacheSizeMaxBytesReaded = false;
char zTexCacheSizeMaxBytes[256];

bool zVidResFullscreenBPPReaded = false;
char zVidResFullscreenBPP[256];

bool extendedMenuReaded = false;
char extendedMenu[256];

bool menuShowVersionReaded = false;
char menuShowVersion[256];

bool zStartupWindowedReaded = false;
char zStartupWindowed[256];

bool InstallIniFix(void)
{
	if(!(zTexCacheSizeMaxBytesReaded = GothicReadIniString("ENGINE", "zTexCacheSizeMaxBytes", "0", zTexCacheSizeMaxBytes, 256, "Gothic.ini")) || (atoi(zTexCacheSizeMaxBytes) < 100000000))
		GothicWriteIniString("ENGINE", "zTexCacheSizeMaxBytes", "100000000", "Gothic.ini");

	if(!(zVidResFullscreenBPPReaded = GothicReadIniString("VIDEO", "zVidResFullscreenBPP", "32", zVidResFullscreenBPP, 256, "Gothic.ini")) || (atoi(zVidResFullscreenBPP) != 32))
		GothicWriteIniString("VIDEO", "zVidResFullscreenBPP", "32", "Gothic.ini");

	if(IsWindows8OrGreater())
	{
		char FixAppCompat[256];
		GothicReadIniString("DEBUG", "FixAppCompat", "1", FixAppCompat, 256, "SystemPack.ini");
		if(atoi(FixAppCompat) == 2)
		{
			if(!(zStartupWindowedReaded = GothicReadIniString("VIDEO", "zStartupWindowed", "1", zStartupWindowed, 256, "Gothic.ini")) || (atoi(zStartupWindowed) != 1))
				GothicWriteIniString("VIDEO", "zStartupWindowed", "1", "Gothic.ini");
		}
	}

	if(!(extendedMenuReaded = GothicReadIniString("INTERNAL", "extendedMenu", "0", extendedMenu, 256, "Gothic.ini")) || (atoi(extendedMenu) != 1))
		GothicWriteIniString("INTERNAL", "extendedMenu", "1", "Gothic.ini");

	if(!(menuShowVersionReaded = GothicReadIniString("INTERNAL", "menuShowVersion", "0", menuShowVersion, 256, "Gothic.ini")) || (atoi(menuShowVersion) != 1))
		GothicWriteIniString("INTERNAL", "menuShowVersion", "1", "Gothic.ini");

	char Buffer[256];
	if(GothicReadIniString("DEBUG", "gameStartFailed", "0", Buffer, 256, "Gothic.ini") && atoi(Buffer))
	{
		GothicWriteIniString("VIDEO", "zVidResFullscreenX", "800", "Gothic.ini");
		GothicWriteIniString("VIDEO", "zVidResFullscreenY", "600", "Gothic.ini");
	}
	GothicWriteIniString("DEBUG", "gameStartFailed", "0", "Gothic.ini");
	GothicWriteIniString("DEBUG", "gameAbnormalExit", "0", "Gothic.ini");

	return true;
}

void RemoveIniFix(void)
{
	if(zTexCacheSizeMaxBytesReaded)
		GothicWriteIniString("ENGINE", "zTexCacheSizeMaxBytes", zTexCacheSizeMaxBytes, "Gothic.ini");
	if(zVidResFullscreenBPPReaded)
		GothicWriteIniString("VIDEO", "zVidResFullscreenBPP", zVidResFullscreenBPP, "Gothic.ini");
	if(zStartupWindowedReaded)
		GothicWriteIniString("VIDEO", "zStartupWindowed", zStartupWindowed, "Gothic.ini");
	if(extendedMenuReaded)
		GothicWriteIniString("INTERNAL", "extendedMenu", extendedMenu, "Gothic.ini");
	if(menuShowVersionReaded)
		GothicWriteIniString("INTERNAL", "menuShowVersion", menuShowVersion, "Gothic.ini");

}