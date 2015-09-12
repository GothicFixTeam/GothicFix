#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>
#include <tchar.h>
#include <windows.h>
#include <VersionHelpers.h>

#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

#include "Common/TypeDefs.h"
#include "Common/Object.h"
#include "Common/Utility.h"

#include "Common/Containers/Array.h"
#include "Common/Containers/String.h"
#include "Common/Containers/HashTable.h"
#include "Common/Containers/TaggedArray.h"

#include "Common/UtilityEx.h"

using namespace COMMON;

#include "Bink/BinkExports.h"
#include "Bink/DLL.h"

#include <opencv\\cv.h>

#ifndef _DEBUG
#pragma comment (lib, "opencv_core249.lib")
#pragma comment (lib, "zlib.lib")
#else
#pragma comment (lib, "opencv_core249d.lib")
#pragma comment (lib, "zlibd.lib")
#endif

#include <vorbis/vorbisfile.h>
#ifdef _DEBUG
#pragma comment(lib, "oggd.lib")
#pragma comment(lib, "vorbisd.lib")
#else
#pragma comment(lib, "ogg.lib")
#pragma comment(lib, "vorbis.lib")
#endif

#include "Vdfs/VdfsIndex.h"
#include "Vdfs/Flows/IFS.h"
#include "Vdfs/Flows/StdFlow.h"
#include "Vdfs/Flows/VdfFlow.h"
#include "Vdfs/Filters/OggFilter.h"
#include "Vdfs/Vdfs.h"

#include "IniUtils.h"
#include "IniUtilsEx.h"
#include "PatchUtils.h"

#include "Fixes/KillerFix.h"
#include "Fixes/FsHook.h"
#include "Fixes/D3DFix.h"
#include "Fixes/GUXFix.h"
#include "Fixes/IniFix.h"
#include "Fixes/BinkFix.h"
#include "Fixes/SplashFix.h"
#include "Fixes/SendMsgFix.h"
#include "Fixes/MssFix.h"
#include "Fixes/SteamOverlayFix.h"

#include "../Vdfs32.h"