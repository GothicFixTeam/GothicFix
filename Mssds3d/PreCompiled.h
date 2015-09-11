#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>
#include <math.h>
#include <tchar.h>
#include <windows.h>

#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

#include <xaudio2.h>
#include <xaudio2fx.h>
#include <x3daudio.h>
#pragma comment(lib, "X3DAudio.lib")

extern bool MssLoad(void);
extern void MssFree(void);

#include "Common/TypeDefs.h"
#include "Common/Object.h"
#include "Common/Utility.h"

#include "Common/Containers/Array.h"
#include "Common/Containers/String.h"
#include "Common/Containers/HashTable.h"

#include "Common/UtilityEx.h"

using namespace COMMON;

#include "IniUtils.h"

#include "Mss.h"
#include "Mssds3d.h"