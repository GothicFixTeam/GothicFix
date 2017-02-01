/*//////////////////////////////////////////////////////////////////////////////
//
//  GothicStarter
//
//////////////////////////////////////////////////////////////////////////////*/

#include "GothicStarter.h"
#include "resource.rh"
#define WIN32_LEAN_AND_MEAN
#define NONAMELESSUNION
#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <richedit.h>
#include <shellapi.h>
#include <tlhelp32.h>

/*//////////////////////////////////////////////////////////////////////////////
//
//  Defines
*/

#define MAX_INFO (0x1000)
#define MAX_BUFF (MAX_INFO + sizeof(long))
#define MAXSTR 0x100

/*//////////////////////////////////////////////////////////////////////////////
//
//  Constants
*/

/* GUI */
#ifndef MOD_VERSION
const LPCTSTR GUI_RTF_HEAD = TEXT("{\\rtf1");
TCHAR GUI_RTF_ANSI[MAXSTR];
const LPCTSTR GUI_RTF_BOLD = TEXT("\\b ");
const LPCTSTR GUI_RTF_PARB = TEXT("\\par\\b0\n");
const LPCTSTR GUI_RTF_PARN = TEXT("\\par\n");
const LPCTSTR GUI_RTF_ENDS = TEXT("}\n");
TCHAR GUI_INF_VERS[MAXSTR];
const LPCTSTR GUI_DSC_NONE = TEXT("<none>");
#else
#define MAX_GUI_ZLOG_TXT 5
const LPCTSTR GUI_ZLOG_TXT[MAX_GUI_ZLOG_TXT] = {
    TEXT(""),
    TEXT("4"),
    TEXT("5"),
    TEXT("8"),
    TEXT("10")
};
#endif

/* Registry (don't translate) */
#define REG_ROOT_KEY HKEY_CURRENT_USER
const LPCTSTR REG_ROOT_SUB = TEXT("Software\\Piranha Bytes\\GothicStarter");
#ifndef MOD_VERSION
const LPCTSTR REG_WND_NPOS = TEXT("Window.Placement");
#else
const LPCTSTR REG_OPT_BASE = TEXT("Options.");
const LPCTSTR REG_OPT_PARA = TEXT("Parameter");
const LPCTSTR REG_OPT_PARS = TEXT("Reparse");
const LPCTSTR REG_OPT_WIND = TEXT("Window");
const LPCTSTR REG_OPT_NMUS = TEXT("NoMusic");
const LPCTSTR REG_OPT_NSND = TEXT("NoSound");
const LPCTSTR REG_OPT_ZSPY = TEXT("LogLevel");
const LPCTSTR REG_OPT_VDFS = TEXT("Physical");
#endif

/* INI (don't translate) */
const LPCTSTR INI_SEC_FILE = TEXT("FILES");
const LPCTSTR INI_FILE_VDF = TEXT("VDF");
const LPCTSTR INI_SEC_INFO = TEXT("INFO");
const LPCTSTR INI_INFO_DSC = TEXT("Description");
const LPCTSTR INI_INFO_MOD = TEXT("Title");
const LPCTSTR INI_INFO_VER = TEXT("Version");
const LPCTSTR INI_INFO_PUB = TEXT("Authors");
const LPCTSTR INI_INFO_URL = TEXT("Webpage");
const LPCTSTR INI_INFO_ICO = TEXT("Icon");
const LPCTSTR INI_SEC_MODS = TEXT("MOD");
const LPCTSTR INI_MOD_BASE = TEXT("Base");
const LPCTSTR INI_SEC_HACK = TEXT("OVERRIDES");
const LPCTSTR INI_SEC_HACK_SP = TEXT("OVERRIDES_SP");
const LPCTSTR TXT_INVALID  = TEXT("!<invalid>");

/*//////////////////////////////////////////////////////////////////////////////
//
//  Globals
*/

static HIMAGELIST g_ImageList;
static HIMAGELIST g_ImageListGothic1;
#define MAX_GOTHIC1_IMAGE_LIST 30
static HINSTANCE g_AppInstance;
static TCHAR g_RootDirectory[MAX_PATH];
static TCHAR g_AppDirectory[MAX_PATH];
static TCHAR g_AutoFocus[MAX_PATH];
static HFONT g_AppFont10;
static HWND g_AppWindow;
static LONG g_AutoStart;
static LONG g_AutoClose;
#ifdef MOD_VERSION
static BOOL g_RunSpacer;
#endif
static BOOL g_IsGothic1;

/* Controls */
static HWND g_ModList;
static HWND g_BtnPlay;
#ifndef MOD_VERSION
static HWND g_RtfDesc;
static HWND g_RtfInfo;
#else
static HWND g_EdtPara;
static HWND g_BtnEdit;
static HWND g_CbxPars;
static HWND g_CbxWind;
static HWND g_CbxNMus;
static HWND g_CbxNSnd;
static HWND g_SpyTBar;
static HWND g_SpyStat;
#endif

/*//////////////////////////////////////////////////////////////////////////////
//
//  Standard Library
//
*/

#ifndef MOD_VERSION
void * __cdecl memcpy(void * dst, const void * src, size_t count)
{
    char *d = (char *)dst;
    char *s = (char *)src;
    while (count--)
        *d++ = *s++;
    return(dst);
}
#endif

/*//////////////////////////////////////////////////////////////////////////////
//
//  Utils
//
*/

const LPCTSTR SBSL = TEXT("\\");
const LPCTSTR SSPC = TEXT(" ");
const LPCTSTR SNUL = TEXT("");
#define TNUL TEXT('\0')
#define TBSL TEXT('\\')
#define TFSL TEXT('/')
#define TSPC TEXT(' ')
#define charof(x) (sizeof(x) / sizeof(TCHAR))
#define lstrend(x) (&x[lstrlen(x) - 1])

LPTSTR __cdecl strcatx(LPTSTR dst, .../*, NULL*/)
{
    va_list arg;
    LPCTSTR str;
    LPTSTR ret = dst;
    va_start(arg, dst);
    do
    {
        str = va_arg(arg, LPCTSTR);
        if (!str)
            break;
        ret = lstrcat(dst, str);
    }
    while (ret);
    va_end(arg);
    return ret;
}

LPTSTR __cdecl strcpyx(LPTSTR dst, LPCTSTR src, .../*, NULL*/)
{
    va_list arg;
    LPCTSTR str;
    LPTSTR ret;
    if ((dst == NULL) || (src == NULL))
        return NULL;
    ret = lstrcpy(dst, src);
    va_start(arg, src);
    do
    {
        str = va_arg(arg, LPCTSTR);
        if (str != NULL)
            ret = lstrcat(dst, str);
    }
    while (str != NULL);
    va_end(arg);
    return ret;
}

LPCTSTR strstrx(LPCTSTR str, LPCTSTR sub, int max)
{
    int len;
    int i;

    if ((str == NULL) || (sub == NULL))
        return NULL;
    if (*sub == TNUL)
        return str;
    len = lstrlen(str) - lstrlen(sub);
    if (len < 0)
        return NULL;
    if ((max < 0) || (max > len))
        max = len;
    for (i = 0; i <= max; i++)
        if (str[i] == *sub)
        {
            BOOL end = TRUE;
            int j;
            for (j = 0; sub[j] != TNUL; j++)
                if (str[i + j] != sub[j])
                {
                    end = FALSE;
                    break;
                }
            if (end)
                return &str[i];
        }
    return NULL;
}

BOOL FileExists(LPCTSTR FileName)
{
    WIN32_FIND_DATA FindData;
    HANDLE FindFile = FindFirstFile(FileName, &FindData);
    return (FindFile == INVALID_HANDLE_VALUE) ? FALSE : FindClose(FindFile);
}

#ifdef MOD_VERSION

BOOL ExeRunning(LPCTSTR ExeFile)
{
    HANDLE Snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (Snapshot != INVALID_HANDLE_VALUE)
    {
        PROCESSENTRY32 ProcessEntry;
        ProcessEntry.dwSize = sizeof(PROCESSENTRY32);
        if (Process32First(Snapshot, &ProcessEntry))
        {
            do
            {
                if (lstrcmpi(ProcessEntry.szExeFile, ExeFile) == 0)
                    return CloseHandle(Snapshot);
            }
            while (Process32Next(Snapshot, &ProcessEntry));
        }
        CloseHandle(Snapshot);
    }
    return FALSE;
}

void UpdateSlider(void)
{
    WORD Pos = LOWORD(SendMessage(g_SpyTBar, TBM_GETPOS, 0, 0));
    if (Pos < MAX_GUI_ZLOG_TXT)
        SetWindowText(g_SpyStat, GUI_ZLOG_TXT[Pos]);
    else
        SetWindowText(g_SpyStat, SNUL);
    SendMessage(g_SpyTBar, TBM_SETSEL, TRUE, Pos << 16);
}

/*//////////////////////////////////////////////////////////////////////////////
//
//  Options
*/

static LONG g_OptionsSaved = FALSE;

void SaveOptionCheckBox(HKEY Key, LPCTSTR Name, int Ctrl)
{
    DWORD Flag;
    TCHAR Buff[1024];
    
    strcpyx(Buff, REG_OPT_BASE, Name, NULL);
    Flag = IsDlgButtonChecked(g_AppWindow, Ctrl) ? 1 : 0;
    RegSetValueEx(Key, Buff, 0, REG_DWORD, (LPBYTE)&Flag, sizeof(DWORD));
}

BOOL SaveOption(void)
{
    static /* __chkstk */
    TCHAR Buff[MAX_BUFF];
    TCHAR Name[1024];
    DWORD Flag;
    HKEY Key;

    if (InterlockedExchange(&g_OptionsSaved, TRUE) == TRUE)
        return TRUE;

    Key = NULL;
    if (RegCreateKeyEx(REG_ROOT_KEY, REG_ROOT_SUB, 0, NULL, 0, KEY_SET_VALUE, NULL, &Key, NULL) != ERROR_SUCCESS)
        return FALSE;

    /* Parameters */
    strcpyx(Name, REG_OPT_BASE, REG_OPT_PARA, NULL);
    GetDlgItemText(g_AppWindow, IDC_PARA, Buff, MAX_INFO + 1);
    RegSetValueEx(Key, Name, 0, REG_SZ, (LPBYTE)&Buff, lstrlen(Buff) + 1);

    /* zSpy-Level */
    strcpyx(Name, REG_OPT_BASE, REG_OPT_ZSPY, NULL);
    Flag = (DWORD)SendMessage(g_SpyTBar, TBM_GETPOS, 0, 0);
    RegSetValueEx(Key, Name, 0, REG_DWORD, (LPBYTE)&Flag, sizeof(DWORD));

    /* Checkboxes */
    SaveOptionCheckBox(Key, REG_OPT_PARS, IDC_PARS);
    SaveOptionCheckBox(Key, REG_OPT_WIND, IDC_WIND);
    SaveOptionCheckBox(Key, REG_OPT_NMUS, IDC_NMUS);
    SaveOptionCheckBox(Key, REG_OPT_NMUS, IDC_NMUS);
    SaveOptionCheckBox(Key, REG_OPT_NSND, IDC_NSND);
    SaveOptionCheckBox(Key, REG_OPT_VDFS, IDC_VDFS);

    RegCloseKey(Key);
    return TRUE;
}

void LoadOptionCheckBox(HKEY Key, LPCTSTR Name, int Ctrl)
{
    TCHAR n[1024];
    DWORD v; DWORD s = sizeof(v);

    strcpyx(n, REG_OPT_BASE, Name, NULL);
    if (RegQueryValueEx(Key, n, NULL, NULL, (LPBYTE)&v, &s) == ERROR_SUCCESS)
        if (v)
            CheckDlgButton(g_AppWindow, Ctrl, BST_CHECKED);
}

BOOL LoadOption(void)
{
    static /* __chkstk */
    TCHAR Buff[MAX_BUFF];
    TCHAR Name[1024];
    DWORD Size;
    DWORD Flag;
    HKEY Key;

    Key = NULL;
    if (RegOpenKeyEx(REG_ROOT_KEY, REG_ROOT_SUB, 0, KEY_QUERY_VALUE, &Key) != ERROR_SUCCESS)
        return FALSE;

    /* Parameters */
    Size = MAX_BUFF;
    strcpyx(Name, REG_OPT_BASE, REG_OPT_PARA, NULL);
    if (RegQueryValueEx(Key, Name, NULL, NULL, (LPBYTE)&Buff, &Size) ==
        ERROR_SUCCESS)
        SetDlgItemText(g_AppWindow, IDC_PARA, Buff);

    strcpyx(Name, REG_OPT_BASE, REG_OPT_ZSPY, NULL);

    /* zSpy-Level */
    Size = sizeof(DWORD);
    if (RegQueryValueEx(Key, Name, NULL, NULL, (LPBYTE)&Flag, &Size) ==
        ERROR_SUCCESS)
    {
        SendMessage(g_SpyTBar, TBM_SETPOS, TRUE, Flag);
        UpdateSlider();
    }

    /* Checkboxes */
    LoadOptionCheckBox(Key, REG_OPT_PARS, IDC_PARS);
    LoadOptionCheckBox(Key, REG_OPT_WIND, IDC_WIND);
    LoadOptionCheckBox(Key, REG_OPT_NMUS, IDC_NMUS);
    LoadOptionCheckBox(Key, REG_OPT_NMUS, IDC_NMUS);
    LoadOptionCheckBox(Key, REG_OPT_NSND, IDC_NSND);
    LoadOptionCheckBox(Key, REG_OPT_VDFS, IDC_VDFS);

    RegCloseKey(Key);
    return TRUE;
}

#else

BOOL SaveWndPos(void)
{
    HKEY Key = NULL;
    BOOL Result = FALSE;
    WINDOWPLACEMENT Placement;
    RtlSecureZeroMemory(&Placement, sizeof(Placement));
    Placement.length = sizeof(WINDOWPLACEMENT);

    if (GetWindowPlacement(g_AppWindow, &Placement))
        if (RegCreateKeyEx(REG_ROOT_KEY, REG_ROOT_SUB, 0, NULL, 0, KEY_WRITE,
            NULL, &Key, NULL) == ERROR_SUCCESS)
        {
            if (RegSetValueEx(Key, REG_WND_NPOS, 0, REG_BINARY,
                (LPBYTE)&Placement.rcNormalPosition,
                sizeof(Placement.rcNormalPosition)) == ERROR_SUCCESS)
                Result = TRUE;
            RegCloseKey(Key);
        }

    return Result;
}

BOOL LoadWndPos(void)
{
    HKEY Key = NULL;
    BOOL Result = FALSE;
    DWORD Type = REG_BINARY;
    WINDOWPLACEMENT Placement;
    DWORD Size  = sizeof(Placement.rcNormalPosition);

    RtlSecureZeroMemory(&Placement, sizeof(Placement));
    Placement.length = sizeof(WINDOWPLACEMENT);
    if (GetWindowPlacement(g_AppWindow, &Placement))
        if (ERROR_SUCCESS == RegOpenKeyEx(REG_ROOT_KEY, REG_ROOT_SUB, 0,
            KEY_QUERY_VALUE, &Key))
        {
            if (ERROR_SUCCESS == RegQueryValueEx(Key, REG_WND_NPOS, NULL, &Type,
                (LPBYTE)&Placement.rcNormalPosition, &Size))
                Result = SetWindowPlacement(g_AppWindow, &Placement);
            RegCloseKey(Key);
        }

    return Result;
}

/*//////////////////////////////////////////////////////////////////////////////
//
//  RTF Streaming
*/

typedef struct _EDITCOOKIE {
    LPCTSTR Data;
    LONG    Size;
    LONG    Pos;
} EDITCOOKIE;

DWORD CALLBACK EditStreamCallback(DWORD Cookie, LPBYTE Data, LONG cb, LONG *pcb)
{
    LONG Size;
    EDITCOOKIE *pCookie = (EDITCOOKIE *)(DWORD_PTR)Cookie;

    if (!pCookie)
        return ERROR_INVALID_PARAMETER;
    if (!pCookie->Data)
        return ERROR_NO_DATA;

    Size = pCookie->Size - pCookie->Pos + 1;
    if (Size <= 0)
        return ERROR_INSUFFICIENT_BUFFER;

    *pcb = (cb < Size) ? cb : Size;
    CopyMemory(Data, &pCookie->Data[pCookie->Pos], *pcb);
    pCookie->Pos += *pcb;

    return ERROR_SUCCESS;
}

ULONG StreamInRtf(HWND Rich, LPCTSTR Data, LONG Size)
{
    WPARAM Flag = SF_TEXT;
    HANDLE File;
    DWORD FileSize = 0;
    PVOID FileData = NULL;
    DWORD FileRead;
    EDITCOOKIE Cookie;
    EDITSTREAM Stream;

    if ((Rich == NULL) || !IsWindow(Rich) || (Data == NULL))
        return ERROR_INVALID_PARAMETER;

    if (strstrx(Data, GUI_RTF_HEAD, 0) == Data)
        Flag = SF_RTF;
    else if (strstrx(Data, TEXT("!<symlink>"), 0) == Data)
    {
        File = CreateFile(&Data[10], GENERIC_READ, 0, NULL, OPEN_EXISTING, 0,
            NULL);
        if (File != INVALID_HANDLE_VALUE)
        {
            FileSize = GetFileSize(File, NULL);
            if ((FileSize > 0) && (FileSize != INVALID_FILE_SIZE))
            {
                FileData = LocalAlloc(LPTR, FileSize + 1);
                if (FileData)
                {
                    FileRead = 0;
                    if (ReadFile(File, FileData, FileSize, &FileRead, NULL) &&
                        (FileRead == FileSize))
                    {
                        if (strstrx(FileData, GUI_RTF_HEAD, 0) == FileData)
                            Flag = SF_RTF;
                    }
                    else
                        FileSize = 0;
                }
            }
            CloseHandle(File);
        }
    }
    if ((FileData != NULL) && (FileSize > 0))
    {
        Cookie.Data = FileData;
        Cookie.Size = FileSize;
    }
    else
    {
        Cookie.Data = Data;
        Cookie.Size = Size;
    }
    Cookie.Pos = 0;
    Stream.dwCookie = (DWORD_PTR)&Cookie;
    Stream.dwError = ERROR_NO_DATA;
    Stream.pfnCallback = EditStreamCallback;
    SendMessage(Rich, EM_STREAMIN, Flag, (LPARAM)&Stream);
    if (FileData != NULL)
        LocalFree(FileData);
    return Stream.dwError;
}

#endif  /* MOD_VERSION */

/*//////////////////////////////////////////////////////////////////////////////
//
//  Mod Infos
*/

typedef struct _INIHACK {
    struct _INIHACK * nxt;
	TCHAR             sec[MAX_BUFF];
	LPTSTR            key;
    LPTSTR            val;
    TCHAR             org[MAX_BUFF];
} INIHACK, * LPINIHACK;

typedef struct _MODINFO {
    TCHAR     name[MAX_PATH];
    TCHAR     base[MAX_PATH];
    TCHAR     vdfs[MAX_BUFF];
#ifndef MOD_VERSION
    TCHAR     desc[MAX_BUFF];
    TCHAR     info[MAX_BUFF * 5];  /* RTF + Title, Version, Authors, Website */
#endif
	LPINIHACK hack;
	LPINIHACK hackSp;
} MODINFO, * LPMODINFO;

BOOL AddModFile(LPCTSTR FilePath)
{
    static /* __chkstk */
    TCHAR Buff[MAX_BUFF];
    
    LPCSTR FileName;
    LPMODINFO Info;
    LPTSTR pSrc;
    LPTSTR pStr;
    LPTSTR pDst;
    HICON Icon;
    int Neg;
    LVITEM Item;
	LPTSTR pOverrides;
	LPTSTR pCurrent;
	LPTSTR pCurrKey;
	LPTSTR pCurrVal;
	LPINIHACK pCurrHack;
	LPINIHACK pLastHack;

    if (FilePath == NULL)
        return FALSE;

    /* FileName */
    FileName = lstrend(FilePath);
    while ((FileName > FilePath) && (*FileName != TBSL) && (*FileName != TFSL))
        if (*FileName-- == TSPC)
            return FALSE;
    if ((*FileName != TBSL) || (*FileName != TFSL))
        FileName++;

    if (!FileExists(FilePath))
        return FALSE;

    /* Validate */
    RtlSecureZeroMemory(&Buff, sizeof(Buff));
    GetPrivateProfileString(INI_SEC_FILE, INI_FILE_VDF, TXT_INVALID, Buff,
        MAX_INFO, FilePath);
    if (lstrcmp(Buff, TXT_INVALID) == 0)
        return FALSE;

    /* Alloc */
    Info = (LPMODINFO)LocalAlloc(LPTR, sizeof(MODINFO));
    if (!Info)
        return FALSE;

    /* Name */
    lstrcpyn(Info->name, FileName, lstrlen(FileName) - 3);
    CharLower(Info->name);

	/* Alias */
	if (!GetPrivateProfileString(INI_SEC_MODS, INI_MOD_BASE, Info->name, Info->base, MAX_PATH, FilePath))
		lstrcpy(Info->base, Info->name);
    CharLower(Info->base);

    /* Volumes */
    pSrc = Buff;
    pStr = pSrc;
    pDst = Info->vdfs;
    while (*pSrc != TNUL)
    {
        if ((TSPC == *pStr) && (TSPC == pStr[1]))
        {
            *pStr = TNUL;
            lstrcpy(pDst, pSrc);
            pDst += lstrlen(pSrc) + 1;
            pSrc = &pStr[2];
            pStr++;
        }
        if (TNUL == *pStr)
        {
            lstrcpy(pDst, pSrc);
        /*  pSrc = pStr; */
            break;
        }
        pStr++;
    }

#ifndef MOD_VERSION

    /* Desc */
    *Buff = TNUL;
    GetPrivateProfileString(INI_SEC_INFO, INI_INFO_DSC, SNUL, Buff, MAX_INFO,
        FilePath);
    if (lstrlen(Buff) <= 0)
        lstrcpy(Buff, GUI_DSC_NONE);
    lstrcpy(Info->desc, Buff);

    /* Info */
    strcpyx(Info->info, GUI_RTF_HEAD, GUI_RTF_ANSI, GUI_RTF_PARN, GUI_RTF_PARN,
		NULL);
    *Buff = TNUL;
    GetPrivateProfileString(INI_SEC_INFO, INI_INFO_MOD, SNUL, Buff, MAX_INFO,
        FilePath);
    if (lstrlen(Buff) <= 0)
        lstrcpy(Buff, FileName);
    strcatx(Info->info, GUI_RTF_BOLD, Buff, GUI_RTF_PARB, NULL);
    *Buff = TNUL;
    GetPrivateProfileString(INI_SEC_INFO, INI_INFO_VER, SNUL, Buff, MAX_INFO,
        FilePath);
    if (lstrlen(Buff) <= 0)
        lstrcpy(Buff, GUI_DSC_NONE);
    strcatx(Info->info, GUI_INF_VERS, Buff, GUI_RTF_PARN, GUI_RTF_PARN, NULL);
    *Buff = TNUL;
    GetPrivateProfileString(INI_SEC_INFO, INI_INFO_PUB, SNUL, Buff, MAX_INFO,
        FilePath);
    if (lstrlen(Buff) > 0)
        strcatx(Info->info, GUI_RTF_BOLD, Buff, GUI_RTF_PARB, NULL);
    *Buff = TNUL;
    GetPrivateProfileString(INI_SEC_INFO, INI_INFO_URL, SNUL, Buff, MAX_INFO,
    FilePath);
    if (lstrlen(Buff) > 0)
        strcatx(Info->info, Buff, GUI_RTF_PARN, NULL);
    strcatx(Info->info, GUI_RTF_PARN, GUI_RTF_ENDS, NULL);

#endif

    /* Icon */
    *Buff = TNUL;
    GetPrivateProfileString(INI_SEC_INFO, INI_INFO_ICO, SNUL, Buff, MAX_INFO,
        FilePath);
    Icon = NULL;
	if (g_IsGothic1 && g_ImageListGothic1 && !lstrcmpi(FileName, TEXT("GothicGame.ini")))
		Icon = ImageList_GetIcon(g_ImageListGothic1, 0, ILD_TRANSPARENT);
	else if (lstrlen(Buff) > 0)
    {
        int Idx = 0;
        LPTSTR pStr = lstrend(Buff);
        while ((pStr > Buff) && (*pStr >= TEXT('0')) && (*pStr <= TEXT('9')))
            pStr--;
		/* Internal Imglist (G1) */
		if (pStr == Buff)
		{
			while (*pStr != TNUL)
			{
				Idx = 10 * Idx + (*pStr & 0x0F);
				pStr++;
			}
			if ((Idx < 1) || (Idx >= MAX_GOTHIC1_IMAGE_LIST))
				Idx = 1;
			if (g_ImageListGothic1)
				Icon = ImageList_GetIcon(g_ImageListGothic1, Idx, ILD_TRANSPARENT);
		}
		else
		{
			/* Extract Icon (G2) */
			if ((pStr > Buff) && (*pStr == TEXT('-')))
				pStr--;
			if ((pStr > Buff) && (*pStr == TEXT(',')))
			{
				*pStr = TNUL;
				pStr++;
				Neg = 1;
				if (*pStr == TEXT('-'))
				{
					Neg = -1;
					pStr++;
				}
				while (*pStr != TNUL)
				{
					Idx = 10 * Idx + (*pStr & 0x0F);
					pStr++;
				}
				Idx *= Neg;
			}
			ExtractIconEx(Buff, Idx, &Icon, NULL, 1);
		}
    }
    if (!Icon)
	{
		if (g_IsGothic1)
			Icon = ImageList_GetIcon(g_ImageListGothic1, 1, ILD_TRANSPARENT);
		else
			Icon = LoadIcon(NULL, (LPCSTR)IDI_APPLICATION);
	}
	ImageList_AddIcon(g_ImageList, Icon);
    DestroyIcon(Icon);

    /* Title */
    Buff[0] = TSPC;
    Buff[1] = TNUL;
#ifdef MOD_VERSION
    lstrcpy(&Buff[1], FileName);
	if (lstrcmpi(Info->name, Info->base))
	{
		lstrcat(Buff, TEXT(" -> "));
		lstrcat(Buff, Info->base);
		lstrcat(Buff, TEXT(".ini"));
	}
#else
    GetPrivateProfileString(INI_SEC_INFO, INI_INFO_MOD, FileName, &Buff[1],
        MAX_INFO, FilePath);
    if (lstrlen(Buff) <= 1)
        lstrcpy(&Buff[1], FileName);
	else
	{	/* Convert RTF \'xx into chars */
		LPTSTR Src = &Buff[1];
		LPTSTR Dst;
		for( Dst = Src; Dst[-1] != TNUL; Dst++ )
			if( Src[0] == TEXT('\\') &&
				Src[1] == TEXT('\'') &&
				((Src[2] >= TEXT('0') && Src[2] <= TEXT('9')) || (Src[2] >= TEXT('A') && Src[2] <= TEXT('F')) || (Src[2] >= TEXT('a') && Src[2] <= TEXT('f')) ) &&
				((Src[3] >= TEXT('0') && Src[3] <= TEXT('9')) || (Src[3] >= TEXT('A') && Src[3] <= TEXT('F')) || (Src[3] >= TEXT('a') && Src[3] <= TEXT('f')) ) )
			{
				if( Src[2] >= TEXT('0') && Src[2] <= TEXT('9') )
                    Dst[0] = (Src[2] - TEXT('0')) << 4;
				else
                    Dst[0] = ((Src[2] | 0x20) - TEXT('a') + 0x0A) << 4;
				if( Src[3] >= TEXT('0') && Src[3] <= TEXT('9') )
                    Dst[0] |= Src[3] - TEXT('0');
				else
                    Dst[0] |= (Src[3] | 0x20) - TEXT('a') + 0x0A;
				Src += 4;
			}
			else
			{
				Dst[0] = Src[0];
				Src++;
			}
	}
#endif

	/* Overrides */
	Info->hack = NULL;
	pOverrides = (LPTSTR)LocalAlloc(LPTR, 32767);  // 32,767 is the maximum on Win9x
    if (pOverrides)
	{
		if (GetPrivateProfileSection(INI_SEC_HACK, pOverrides, 32767, FilePath))
		{
			pCurrent = pOverrides;
			pLastHack = NULL;
			while (pCurrent[0])
			{
				pCurrHack = (LPINIHACK)LocalAlloc(LPTR, sizeof(INIHACK));
				if (pCurrHack)
				{
					pCurrHack->nxt = NULL;
					lstrcpyn(pCurrHack->sec, pCurrent, MAX_BUFF);
					pCurrVal = &(pCurrHack->sec[0]);
					while (pCurrVal[0] && (pCurrVal[0] != TEXT('=')))
						pCurrVal++;
					if (pCurrVal[0])
					{
						pCurrVal[0] = 0;
						pCurrVal++;
					}
					pCurrKey = &(pCurrHack->sec[0]);
					while (pCurrKey[0] && (pCurrKey[0] != TEXT('.')))
						pCurrKey++;
					if (pCurrKey[0])
					{
						pCurrKey[0] = 0;
						pCurrKey++;
					}
					if (!pCurrHack->sec[0] || !pCurrKey[0])
						LocalFree((HLOCAL)pCurrHack);
					else
					{
						pCurrHack->key = pCurrKey;
						pCurrHack->val = pCurrVal;
						if (pLastHack)
							pLastHack->nxt = pCurrHack;
						else
							Info->hack = pCurrHack;
						pLastHack = pCurrHack;
					}
				}
				while (pCurrent[0])
					pCurrent++;
				pCurrent++;
			}
		}
		LocalFree((HLOCAL)pOverrides);
	}

	/* Overrides System Pack */
	Info->hackSp = NULL;
	pOverrides = (LPTSTR)LocalAlloc(LPTR, 32767);  // 32,767 is the maximum on Win9x
    if (pOverrides)
	{
		if (GetPrivateProfileSection(INI_SEC_HACK_SP, pOverrides, 32767, FilePath))
		{
			pCurrent = pOverrides;
			pLastHack = NULL;
			while (pCurrent[0])
			{
				pCurrHack = (LPINIHACK)LocalAlloc(LPTR, sizeof(INIHACK));
				if (pCurrHack)
				{
					pCurrHack->nxt = NULL;
					lstrcpyn(pCurrHack->sec, pCurrent, MAX_BUFF);
					pCurrVal = &(pCurrHack->sec[0]);
					while (pCurrVal[0] && (pCurrVal[0] != TEXT('=')))
						pCurrVal++;
					if (pCurrVal[0])
					{
						pCurrVal[0] = 0;
						pCurrVal++;
					}
					pCurrKey = &(pCurrHack->sec[0]);
					while (pCurrKey[0] && (pCurrKey[0] != TEXT('.')))
						pCurrKey++;
					if (pCurrKey[0])
					{
						pCurrKey[0] = 0;
						pCurrKey++;
					}
					if (!pCurrHack->sec[0] || !pCurrKey[0])
						LocalFree((HLOCAL)pCurrHack);
					else
					{
						pCurrHack->key = pCurrKey;
						pCurrHack->val = pCurrVal;
						if (pLastHack)
							pLastHack->nxt = pCurrHack;
						else
							Info->hackSp = pCurrHack;
						pLastHack = pCurrHack;
					}
				}
				while (pCurrent[0])
					pCurrent++;
				pCurrent++;
			}
		}
		LocalFree((HLOCAL)pOverrides);
	}

	/* Add Item */
    RtlSecureZeroMemory(&Item, sizeof(LVITEM));
    Item.iItem = ListView_GetItemCount(g_ModList);
    Item.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;
    if (lstrcmpi(FileName, g_AutoFocus) == 0)
    {
        Item.mask |= LVIF_STATE;
        Item.state = LVIS_SELECTED | LVIS_FOCUSED;
        Item.stateMask = LVIS_SELECTED | LVIS_FOCUSED;
    }
    Item.pszText = Buff;
    Item.iImage = Item.iItem;
    Item.lParam = (LPARAM)Info;
    ListView_InsertItem(g_ModList, &Item);

	return TRUE;
}

LPMODINFO GetModInfo(void)
{
    if (ListView_GetSelectedCount(g_ModList) == 1)
    {
        LVITEM Item;
        RtlSecureZeroMemory(&Item, sizeof(LVITEM));
        Item.mask = LVIF_PARAM;
        Item.iItem = (int)SendMessage(g_ModList, LVM_GETNEXTITEM, (WPARAM)-1, LVNI_SELECTED);
        if (ListView_GetItem(g_ModList, &Item) && (Item.lParam != 0))
            return (LPMODINFO)Item.lParam;
    }
    return NULL;
}

/*//////////////////////////////////////////////////////////////////////////////
//
//  Move Mod Files
*/

BOOL MyCopyFile(LPCTSTR Src, LPCTSTR Dst)
{
    HANDLE Source;
    FILETIME Created;
    FILETIME Touched;
    FILETIME Written;
    HANDLE Dest;

    if (!FileExists(Src))
        return FALSE;

    Source = CreateFile(Src, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
    if (Source != INVALID_HANDLE_VALUE)
    {
        if (!GetFileTime(Source, &Created, &Touched, &Written))
            CloseHandle(Source);
        else
        {
            CloseHandle(Source);
            if (CopyFile(Src, Dst, FALSE))
            {
                Dest = CreateFile(Dst, FILE_WRITE_ATTRIBUTES, 0, NULL,
                    OPEN_EXISTING, 0, NULL);
                if (Dest != INVALID_HANDLE_VALUE)
                {
                    if (SetFileTime(Dest, &Created, &Touched, &Written))
                        return CloseHandle(Dest);
                    else
                        CloseHandle(Dest);
                }
            }
        }
    }
    return FALSE;
}

BOOL MyMoveFile(LPCTSTR Src, LPCTSTR Dst)
{
    if (!FileExists(Src))
        return FALSE;
	if (!lstrcmpi(Src, Dst))
		return TRUE;

	while(FileExists(Dst))
		DeleteFile(Dst);  /* FIXME: deadlock if not deletable */

	return MoveFile(Src, Dst);
}

void MoveModFiles(LPMODINFO Info)
{
    TCHAR DataDir[MAX_PATH];
    TCHAR ModsDir[MAX_PATH];
    TCHAR DatName[MAX_PATH];
    TCHAR ModName[MAX_PATH];
    TCHAR FileMask[MAX_PATH];
    WIN32_FIND_DATA FindData;
    HANDLE FindFile;
    LPTSTR FileName;

    /* Dirs */
    strcpyx(DataDir, g_RootDirectory, TEXT("Data\\"), NULL);
    strcpyx(ModsDir, DataDir, TEXT("modvdf"), NULL);
    if (!FileExists(ModsDir))
        CreateDirectory(ModsDir, NULL);
    lstrcat(ModsDir, SBSL);
    
    /* Clean */
    strcpyx(FileMask, DataDir, TEXT("*.mod"), NULL);
    FindFile = FindFirstFile(FileMask, &FindData);
    if (FindFile != INVALID_HANDLE_VALUE)
    {
        do
        {
            strcpyx(DatName, DataDir, FindData.cFileName, NULL);
            strcpyx(ModName, ModsDir, FindData.cFileName, NULL);
			MyMoveFile(DatName, ModName);
        }
        while(FindNextFile(FindFile, &FindData));
        FindClose(FindFile);
    }

    /* Enable */
    if (Info)
    {
        FileName = Info->vdfs;
        while (*FileName)
        {
            strcpyx(FileMask, ModsDir, FileName, NULL);
            FindFile = FindFirstFile(FileMask, &FindData);
            if (FindFile != INVALID_HANDLE_VALUE)
            {
                strcpyx(ModName, ModsDir, FindData.cFileName, NULL);
                strcpyx(DatName, DataDir, FindData.cFileName, NULL);
				MyMoveFile(ModName, DatName);
                FindClose(FindFile);
            }
            FileName += lstrlen(FileName) + 1;
        }
    }
}

/*//////////////////////////////////////////////////////////////////////////////
//
//  Start Mod
*/

static LONG g_ModRunning = FALSE;

void StartSelectedMod(HWND hDlg)
{
    LPMODINFO info;
    HWND focus;
    HMENU menu;
    TCHAR vdfs_org[MAX_PATH];
    TCHAR vdfs_mod[MAX_PATH];
    TCHAR gini[MAX_PATH];
	TCHAR spini[MAX_PATH];
    PROCESS_INFORMATION pi;
    STARTUPINFO si;
#ifndef MOD_VERSION
    TCHAR cmnd[MAX_PATH * 2];
#else
    static /* __chkstk */
    TCHAR cmnd[MAX_PATH + MAX_BUFF];
#endif
    MSG msg;
    BOOL ret;
    int len = 0;
    LPVOID msg_ = NULL;
    LPTSTR txt;
#ifdef MOD_VERSION
    WORD pos;
    TCHAR spyRoot[MAX_PATH];
    TCHAR spyPath[MAX_PATH];
    PROCESS_INFORMATION spy;
#endif
    TCHAR *StrPos;
	LPINIHACK pCurrHack;
	HWND SmartHeap;
	HWND OK_Button;
	DWORD SmartPID;
	TCHAR filename[MAX_PATH];
	TCHAR base_org[MAX_PATH];
    TCHAR base_tmp[MAX_PATH];

    info = GetModInfo();
    if (!info)
        return;

    if (InterlockedExchange(&g_ModRunning, TRUE) == FALSE)
    {
        /* view */
        focus = GetFocus();
        EnableWindow(GetDlgItem(hDlg, IDC_LIST), FALSE);
        EnableWindow(g_BtnPlay, FALSE);
#ifdef MOD_VERSION
        EnableWindow(g_EdtPara, FALSE);
        EnableWindow(g_BtnEdit, FALSE);
        EnableWindow(g_CbxPars, FALSE);
        EnableWindow(g_CbxWind, FALSE);
        EnableWindow(g_CbxNMus, FALSE);
        EnableWindow(g_CbxNSnd, FALSE);
        EnableWindow(g_SpyTBar, FALSE);
        EnableWindow(GetDlgItem(hDlg, IDC_ZTEX), FALSE);
        EnableWindow(GetDlgItem(hDlg, IDC_AUTO), FALSE);
        EnableWindow(GetDlgItem(hDlg, IDC_CALL), FALSE);
		EnableWindow(GetDlgItem(hDlg, IDC_VDFS), FALSE);
#endif
        SetClassLong(hDlg, GCL_STYLE, GetClassLong(hDlg, GCL_STYLE) | CS_NOCLOSE);
        menu = GetSystemMenu(hDlg, FALSE);
        if (menu)
            EnableMenuItem(menu, SC_CLOSE, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
        DrawMenuBar(hDlg);
        {
			/* mods */
            MoveModFiles(info);
			/* base */
			if (lstrcmpi(info->name, info->base))
			{
				strcpyx(filename, g_AppDirectory, info->name, TEXT(".ini"), NULL);
				strcpyx(base_org, g_AppDirectory, info->base, TEXT(".ini"), NULL);
				if (!FileExists(base_org))
					base_tmp[0] = 0;
				else
				{
					if (!GetTempFileName(g_AppDirectory, TEXT("ini"), 0, base_tmp))
						lstrcpy(base_tmp, TEXT("ini12345.tmp"));
					MyMoveFile(base_org, base_tmp);
				}
				MyCopyFile(filename, base_org);
			}
			/* hack */
			strcpyx(gini, g_AppDirectory, TEXT("Gothic.ini"), NULL);
			pCurrHack = info->hack;
			while (pCurrHack)
			{
				if (!GetPrivateProfileString(pCurrHack->sec, pCurrHack->key, TXT_INVALID, pCurrHack->org, MAX_BUFF, gini))
					lstrcpy(pCurrHack->org, TXT_INVALID);
				if (lstrcmp(pCurrHack->org, TXT_INVALID))
					WritePrivateProfileString(pCurrHack->sec, pCurrHack->key, pCurrHack->val, gini);
				pCurrHack = pCurrHack->nxt;
			}

			/* hack system pack */
			strcpyx(spini, g_AppDirectory, TEXT("SystemPack.ini"), NULL);
			pCurrHack = info->hackSp;
			while (pCurrHack)
			{
				if (!GetPrivateProfileString(pCurrHack->sec, pCurrHack->key, TXT_INVALID, pCurrHack->org, MAX_BUFF, spini))
					lstrcpy(pCurrHack->org, TXT_INVALID);
				if (lstrcmp(pCurrHack->org, TXT_INVALID))
					WritePrivateProfileString(pCurrHack->sec, pCurrHack->key, pCurrHack->val, spini);
				pCurrHack = pCurrHack->nxt;
			}

            /* vdfs */
			if (!g_IsGothic1)
			{
				strcpyx(vdfs_org, g_RootDirectory, TEXT("VDFS.DMP"), NULL);
				strcpyx(vdfs_mod, g_RootDirectory, TEXT("vdfs_"), info->base, TEXT(".dmp"), NULL);
				if (FileExists(vdfs_mod))
				{
					WritePrivateProfileString(TEXT("INTERNAL"), TEXT("gameAbnormalExit"), TEXT("0"), gini);
					WritePrivateProfileString(NULL, NULL, NULL, gini);
					MyCopyFile(vdfs_mod, vdfs_org);
					DeleteFile(vdfs_mod);
				}
			}
			/* exec */
            RtlSecureZeroMemory(&si, sizeof(STARTUPINFO));
            si.cb = sizeof(STARTUPINFO);
            si.dwFlags = STARTF_USESHOWWINDOW;
            si.wShowWindow = SW_SHOWNORMAL;
            strcpyx(cmnd, TEXT("\""), g_AppDirectory, NULL);
#ifdef MOD_VERSION
            if (g_RunSpacer)
			{
				if (g_IsGothic1)
                    lstrcat(cmnd, TEXT("Spacer.exe"));
				else
					lstrcat(cmnd, TEXT("Spacer2.exe"));
			}
			else
#endif
			{
				if (g_IsGothic1)
	                lstrcat(cmnd, TEXT("GothicMod.exe"));
				else
					lstrcat(cmnd, TEXT("Gothic2.exe"));
			}
			strcatx(cmnd, TEXT("\" "), TEXT("-game:"), info->base, TEXT(".ini"), NULL);
#ifdef MOD_VERSION
            if (IsDlgButtonChecked(hDlg, IDC_PARS))
				strcatx(cmnd, SSPC, TEXT("-zreparse"), NULL);
            if (IsDlgButtonChecked(hDlg, IDC_WIND))
                strcatx(cmnd, SSPC, TEXT("-zwindow"), NULL);
            if (IsDlgButtonChecked(hDlg, IDC_NMUS))
                strcatx(cmnd, SSPC, TEXT("-znomusic"), NULL);
            if (IsDlgButtonChecked(hDlg, IDC_NSND))
                strcatx(cmnd, SSPC, TEXT("-znosound"), NULL);
            pos = LOWORD(SendMessage(g_SpyTBar, TBM_GETPOS, 0, 0));
            if (pos > 0)
            {
                strcatx(cmnd, SSPC, TEXT("-zlog:"), NULL);
                switch (pos)
                {
                    case 1: lstrcat(cmnd, TEXT("4")); break;
                    case 3: lstrcat(cmnd, TEXT("8")); break;
                    case 4: lstrcat(cmnd, TEXT("10")); break;
                    default: lstrcat(cmnd, TEXT("5")); break;
                }
                lstrcat(cmnd, TEXT(",s"));
                if (!ExeRunning(TEXT("zSpy.exe")))
                {
                    si.wShowWindow = SW_SHOWMINNOACTIVE;
                    strcpyx(spyRoot, g_RootDirectory, TEXT("_work\\tools\\zSpy\\"), NULL);
                    strcpyx(spyPath, spyRoot, TEXT("zSpy.exe"), NULL);
					if (!FileExists(spyPath))
					{
						strcpyx(spyRoot, g_AppDirectory, NULL);
						strcpyx(spyPath, spyRoot, TEXT("zSpy.exe"), NULL);
					}
					if (CreateProcess(spyPath, NULL, NULL, NULL, FALSE, 0, NULL, spyRoot, &si, &spy))
                    {
						WaitForInputIdle(spy.hProcess, INFINITE);
						CloseHandle(spy.hProcess);
                        CloseHandle(spy.hThread);
                    }
                }
            }
            if (IsDlgButtonChecked(hDlg, IDC_ZTEX))
                strcatx(cmnd, SSPC, TEXT("-ztexconvert"), NULL);
            if (IsDlgButtonChecked(hDlg, IDC_AUTO))
                strcatx(cmnd, SSPC, TEXT("-zautoconvertdata"), NULL);
            if (IsDlgButtonChecked(hDlg, IDC_CALL))
                strcatx(cmnd, SSPC, TEXT("-zconvertall"), NULL);
            if (IsDlgButtonChecked(hDlg, IDC_VDFS))
                strcatx(cmnd, SSPC, TEXT("-vdfs:physicalfirst"), NULL);
            if (!g_AutoClose && (SendMessage(g_EdtPara, WM_GETTEXTLENGTH, 0, 0) > 0))
            {
                lstrcat(cmnd, SSPC);
                GetDlgItemText(hDlg, IDC_PARA, &cmnd[lstrlen(cmnd)], charof(cmnd) - lstrlen(cmnd));
            }
#endif
			si.wShowWindow = SW_SHOWNORMAL;
            if (CreateProcess(NULL, cmnd, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
            {
                //ShowWindow(hDlg, SW_MINIMIZE);
                do
                {
                    /* dialog */
                    do
                    {
                        ret = PeekMessage(&msg, hDlg, 0, 0, TRUE);
                        if ((ret != -1) && ret && !IsDialogMessage(hDlg, &msg))
                        {
                            TranslateMessage(&msg);
                            DispatchMessage(&msg);
                        }
                    }
                    while((ret != -1) && ret);
					/* Hack SmartHeap error message away */
					SmartHeap = FindWindow(TEXT("#32770"), TEXT("SmartHeap Library"));
					if (SmartHeap)
					{
						SmartPID = 0;
						GetWindowThreadProcessId(SmartHeap, &SmartPID);
						if (SmartPID == pi.dwProcessId)
						{
							OK_Button = GetWindow(SmartHeap, GW_CHILD);
							SendMessage(SmartHeap, WM_COMMAND, BN_CLICKED << 16 | GetDlgCtrlID(OK_Button), (LPARAM)OK_Button);
						}
					}
                }
                while ((ret != -1) && (WAIT_TIMEOUT == WaitForSingleObject(pi.hProcess, 500)));
                CloseHandle(pi.hProcess);
                CloseHandle(pi.hThread);
                /* vdfs */
                if (!g_IsGothic1)
				{
					if (GetPrivateProfileInt(TEXT("INTERNAL"), TEXT("gameAbnormalExit"), 1, gini) == 0)
						MyCopyFile(vdfs_org, vdfs_mod);
				}
			}
            else
            {
                if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&msg_, 0, NULL))
                    len = lstrlen((LPTSTR)msg_);
                txt = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, len + 2048);
                if (txt)
                {
                    if (lstrlen(cmnd) > 1024)
                    {
                        cmnd[1024] = TNUL;
                        lstrcat(cmnd, TEXT(" [...]"));
                    }
                    strcpyx(txt, cmnd, TEXT("\n\n"), (LPTSTR)msg_, NULL);
                    StrPos = (LPTSTR)strstrx(txt, TEXT("-game:"), -1);
                    if (StrPos)
                        *--StrPos = TEXT('\n');
                    MessageBox(hDlg, txt, TEXT("GothicStarter"), MB_OK | MB_ICONERROR);
                    HeapFree(GetProcessHeap(), 0, txt);
                }
                if (msg_)
                    LocalFree(msg_);

                    
            }
			/* hack */
			pCurrHack = info->hack;
			while (pCurrHack)
			{
				if (lstrcmp(pCurrHack->org, TXT_INVALID))
					WritePrivateProfileString(pCurrHack->sec, pCurrHack->key, pCurrHack->org, gini);
				pCurrHack = pCurrHack->nxt;
			}
			/* hack system pack */
			pCurrHack = info->hackSp;
			while (pCurrHack)
			{
				if (lstrcmp(pCurrHack->org, TXT_INVALID))
					WritePrivateProfileString(pCurrHack->sec, pCurrHack->key, pCurrHack->org, spini);
				pCurrHack = pCurrHack->nxt;
			}
			/* base */
			if (lstrcmpi(info->name, info->base))
			{
				if (base_tmp[0])
					MyMoveFile(base_tmp, base_org);
				else
					DeleteFile(base_org);
			}
			/* mods */
			MoveModFiles(NULL);
		}
        /* view */
        menu = GetSystemMenu(hDlg, FALSE);
        if (menu)
            EnableMenuItem(menu, SC_CLOSE, MF_BYCOMMAND | MF_ENABLED);
        SetClassLong(hDlg, GCL_STYLE, GetClassLong(hDlg, GCL_STYLE) & ~CS_NOCLOSE);
        DrawMenuBar(hDlg);
#ifdef MOD_VERSION
		EnableWindow(GetDlgItem(hDlg, IDC_VDFS), TRUE);
        EnableWindow(GetDlgItem(hDlg, IDC_CALL), TRUE);
        EnableWindow(GetDlgItem(hDlg, IDC_AUTO), TRUE);
        EnableWindow(GetDlgItem(hDlg, IDC_ZTEX), TRUE);
        EnableWindow(g_SpyTBar, TRUE);
        EnableWindow(g_CbxNSnd, TRUE);
        EnableWindow(g_CbxNMus, TRUE);
        EnableWindow(g_CbxWind, TRUE);
        EnableWindow(g_CbxPars, TRUE);
        EnableWindow(g_BtnEdit, TRUE);
        EnableWindow(g_EdtPara, TRUE);
#endif
        EnableWindow(g_BtnPlay, TRUE);
        EnableWindow(GetDlgItem(hDlg, IDC_LIST), TRUE);
        if (focus)
            SetFocus(focus);
        InterlockedExchange(&g_ModRunning, FALSE);
        if (InterlockedExchange(&g_AutoClose, FALSE) == TRUE)
            SendMessage(hDlg, WM_CLOSE, 0, 0);
        else if (IsIconic(hDlg))
            ShowWindow(hDlg, SW_RESTORE);
    }
}

/*//////////////////////////////////////////////////////////////////////////////
//
//  Dialog
*/

static POINT mintrack;
#ifndef MOD_VERSION
static POINT dlgspace;
static POINT itmspace;
static POINT playsize;
#endif

INT_PTR CALLBACK DlgProc(HWND Dialog, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    HDC dc;
    RECT rect;
#ifndef MOD_VERSION
    RECT rect2;
    LONG playx;
#endif
    HICON icon;
    ENLINK* link;
    TEXTRANGE range;
    static /* __chkstk */
    TCHAR buff[MAX_BUFF];
    LVCOLUMN col;
    HANDLE find;
    WIN32_FIND_DATA fdat;
    LPMODINFO info;

    switch (Msg)
    {
        /* Init */
        case WM_INITDIALOG:

            g_AppWindow = Dialog;
            g_ImageList = ImageList_Create(32, 32, ILC_COLORDDB|ILC_MASK, 0, 1);
			g_ImageListGothic1 = ImageList_LoadBitmap(g_AppInstance, 
				MAKEINTRESOURCE(IDB_LIST), 32, MAX_GOTHIC1_IMAGE_LIST,
				RGB(0xFF, 0x00, 0xFF));
			g_ModList = GetDlgItem(Dialog, IDC_LIST);

            /* Controls */
            g_BtnPlay = GetDlgItem(Dialog, IDC_PLAY);
            #ifndef MOD_VERSION
            g_RtfDesc = GetDlgItem(Dialog, IDC_RICH);
            g_RtfInfo = GetDlgItem(Dialog, IDC_INFO);
            #else
            g_EdtPara = GetDlgItem(Dialog, IDC_PARA);
            SendMessage(g_EdtPara, EM_SETLIMITTEXT, MAX_INFO, 0);
            g_BtnEdit = GetDlgItem(Dialog, IDC_EDIT);
            g_CbxPars = GetDlgItem(Dialog, IDC_PARS);
            g_CbxWind = GetDlgItem(Dialog, IDC_WIND);
            g_CbxNMus = GetDlgItem(Dialog, IDC_NMUS);
            g_CbxNSnd = GetDlgItem(Dialog, IDC_NSND);
            g_SpyTBar = GetDlgItem(Dialog, IDC_ZSPY);
            g_SpyStat = GetDlgItem(Dialog, IDC_ZLOG);
            #endif
            
            /* Size */
            GetWindowRect(Dialog, &rect);
            mintrack.x = rect.right - rect.left;
            mintrack.y = rect.bottom - rect.top;
            #ifndef MOD_VERSION
            GetWindowRect(g_ModList, &rect);
            MapWindowPoints(HWND_DESKTOP, Dialog, (LPPOINT)&rect, 2);
            dlgspace.x = rect.left;
            dlgspace.y = rect.top;
            #endif
            #ifndef MOD_VERSION
            GetWindowRect(g_BtnPlay, &rect2);
            MapWindowPoints(HWND_DESKTOP, Dialog, (LPPOINT)&rect2, 2);
            playsize.x = rect2.right - rect2.left + 1;
            playsize.y = rect2.bottom - rect2.top + 1;
            itmspace.x = rect2.left - rect.right;
            GetWindowRect(g_RtfInfo, &rect);
            MapWindowPoints(HWND_DESKTOP, Dialog, (LPPOINT)&rect, 2);
            itmspace.y = rect.top - rect2.bottom;
            #endif

            if (g_IsGothic1 && g_ImageListGothic1)
				icon = ImageList_GetIcon(g_ImageListGothic1, 0, ILD_TRANSPARENT);
			else
                icon = LoadIcon(g_AppInstance, MAKEINTRESOURCE(IDI_MAIN));
            SendMessage(Dialog, WM_SETICON, ICON_BIG, (LPARAM)icon);
            SendMessage(Dialog, WM_SETICON, ICON_SMALL, (LPARAM)icon);

            if (NULL != (dc = GetDC(Dialog)))
            {
                if (NULL != (g_AppFont10 = CreateFont(-MulDiv(10, GetDeviceCaps(dc, LOGPIXELSY), 72),
                    0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
                    OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                    DEFAULT_PITCH | FF_DONTCARE, TEXT("MS Shell Dlg"))))
                {
                    SendMessage(g_ModList, WM_SETFONT, (WPARAM)g_AppFont10, TRUE);
                    SendMessage(g_BtnPlay, WM_SETFONT, (WPARAM)g_AppFont10, TRUE);
                    #ifdef MOD_VERSION
                    SendMessage(g_BtnEdit, WM_SETFONT, (WPARAM)g_AppFont10, TRUE);
                    #endif
                }
                ReleaseDC(Dialog, dc);
            }
            SendMessage(g_ModList, LVM_SETIMAGELIST, LVSIL_SMALL, (LPARAM)g_ImageList);
            SendMessage(g_ModList, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
            SendMessage(g_ModList, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FLATSB, LVS_EX_FLATSB);
            GetWindowRect(g_ModList, &rect);
            RtlSecureZeroMemory(&col, sizeof(LVCOLUMN));
            col.mask        = LVCF_TEXT | LVCF_WIDTH;
            col.cx          = rect.right - rect.left - GetSystemMetrics(SM_CXVSCROLL) - 2 * GetSystemMetrics(SM_CXEDGE);
            col.pszText     = TEXT("");
            ListView_InsertColumn(g_ModList, 0, &col);

            #ifndef MOD_VERSION
            SendMessage(g_RtfDesc, EM_SETEVENTMASK, 0, ENM_LINK | SendMessage(g_RtfDesc, EM_GETEVENTMASK, 0, 0));
            SendMessage(g_RtfDesc, EM_AUTOURLDETECT, TRUE, 0);
            SendMessage(g_RtfInfo, EM_SETEVENTMASK, 0, ENM_LINK | SendMessage(g_RtfInfo, EM_GETEVENTMASK, 0, 0));
            SendMessage(g_RtfInfo, EM_AUTOURLDETECT, TRUE, 0);
            SendMessage(g_RtfInfo, EM_SETBKGNDCOLOR, (LPARAM)FALSE, (WPARAM)GetSysColor(COLOR_BTNFACE));
            #else
            SendMessage(g_SpyTBar, TBM_SETRANGE, TRUE, 4 << 16);
            SendMessage(g_SpyTBar, TBM_SETPAGESIZE, 0, 1);
            SendMessage(g_SpyTBar, TBM_SETLINESIZE, 0, 1);
            SendMessage(g_SpyTBar, TBM_SETPOS, TRUE, 2);
            UpdateSlider();
            #endif

            strcpyx(buff, g_AppDirectory, TEXT("GothicGame.ini"), NULL);
            AddModFile(buff);
            strcpyx(buff, g_AppDirectory, TEXT("*.ini"), NULL);
            find = FindFirstFile(buff, &fdat);
            if (find != INVALID_HANDLE_VALUE)
            {
                do
                {
                    if (lstrcmpi(fdat.cFileName, TEXT("GothicGame.ini")) == 0)
                        continue;
                    strcpyx(buff, g_AppDirectory, fdat.cFileName, NULL);
                    AddModFile(buff);
                }
                while(FindNextFile(find, &fdat));
                FindClose(find);
            }

            #ifndef MOD_VERSION
            LoadWndPos();
            #else
            LoadOption();
            #endif

            return TRUE;

        case WM_NOTIFY:

            switch (((LPNMHDR)lParam)->code)
            {
                case EN_LINK:

                    link = (ENLINK*)lParam;
                    if ((WM_LBUTTONDOWN == link->msg) && (link->chrg.cpMin - link->chrg.cpMax < 2048))
                    {
                        *buff = TNUL;
                        range.chrg.cpMin = link->chrg.cpMin;
                        range.chrg.cpMax = link->chrg.cpMax;
                        range.lpstrText = buff;
                        SendMessage(link->nmhdr.hwndFrom, EM_GETTEXTRANGE, 0, (LPARAM)&range);
                        if (lstrlen(buff) > 0)
                            return ((LONG_PTR)ShellExecute(Dialog, TEXT("open"), buff, 0, 0, SW_SHOWNORMAL) > 32);
                    }
                    return FALSE;

                case LVN_ITEMCHANGED:

                    EnableWindow(g_BtnPlay, FALSE);
                    #ifndef MOD_VERSION
                    SetWindowText(g_RtfInfo, SNUL);
                    SetWindowText(g_RtfDesc, SNUL);
                    #else
                    EnableWindow(g_BtnEdit, FALSE);
                    #endif
                    info = GetModInfo();
                    if (info)
                    {
                        EnableWindow(g_BtnPlay, TRUE);
                        #ifdef MOD_VERSION
                        EnableWindow(g_BtnEdit, TRUE);
                        #else
                        StreamInRtf(g_RtfInfo, (LPCTSTR)info->info, lstrlen(info->info));
                        StreamInRtf(g_RtfDesc, (LPCTSTR)info->desc, lstrlen(info->desc));
                        #endif
                    }
                    break;

                case LVN_ITEMACTIVATE:

                    #ifdef MOD_VERSION
                    g_RunSpacer = ((GetKeyState(VK_LSHIFT) < 0) || (GetKeyState(VK_RSHIFT) < 0));
                    #endif
                    StartSelectedMod(Dialog);
                    return FALSE;

            }
            break;

        case WM_COMMAND:

            if (HIWORD(wParam) == BN_CLICKED)
            {
                switch (LOWORD(wParam))
                {
                    case IDC_PLAY:

                    #ifdef MOD_VERSION
                    case IDC_EDIT:
                        g_RunSpacer = (IDC_EDIT == LOWORD(wParam));
                    #endif

                        StartSelectedMod(Dialog);
                        break;
                }
            }
            break;

        case WM_SHOWWINDOW:

            if (wParam && InterlockedExchange(&g_AutoStart, FALSE))
                StartSelectedMod(Dialog);
            break;

        case WM_GETMINMAXINFO:

            ((LPMINMAXINFO)lParam)->ptMinTrackSize = mintrack;
            break;

        #ifndef MOD_VERSION

        case WM_SIZE:

            if ((SIZE_RESTORED == wParam) || (SIZE_MAXIMIZED == wParam))
            {
                playx = playsize.x;
                if (LOWORD(lParam) > mintrack.x)
                    playx += (LOWORD(lParam) - mintrack.x) / 4;
                rect.right = LOWORD(lParam) - playx - dlgspace.x + 1;
                rect.left = rect.right - dlgspace.x - itmspace.x + 1;
                rect.bottom = (HIWORD(lParam) - 2 * dlgspace.y + 1) - HIWORD(lParam) * 16 / 46;
                MoveWindow(g_ModList, dlgspace.x, dlgspace.y, rect.left, rect.bottom - dlgspace.y - itmspace.y + 1, TRUE);
                RtlSecureZeroMemory(&col, sizeof(LVCOLUMN));
                col.mask = LVCF_WIDTH;
                col.cx = rect.left - GetSystemMetrics(SM_CXVSCROLL) - 2 * GetSystemMetrics(SM_CXEDGE);
                col.pszText = TEXT("");
                ListView_SetColumn(g_ModList, 0, &col);
                MoveWindow(g_BtnPlay, rect.right, dlgspace.y, playx, playsize.y, TRUE);
                MoveWindow(g_RtfInfo, rect.right, dlgspace.y + playsize.y + itmspace.y, playx, rect.bottom - dlgspace.y - playsize.y - 2 * itmspace.y + 1, TRUE);
                MoveWindow(g_RtfDesc, dlgspace.x, rect.bottom + 1, LOWORD(lParam) - 2 * dlgspace.x + 1, HIWORD(lParam) - rect.bottom - dlgspace.y - 1, TRUE);
            }
            break;

        #else

        case WM_HSCROLL:
            if (GetDlgItem(Dialog, IDC_ZSPY) == (HWND)lParam)
            {
                UpdateSlider();
                return FALSE;
            }
            return TRUE;

        #endif

        case WM_CLOSE:

            #ifndef MOD_VERSION
            SaveWndPos();
            #else
            SaveOption();
            #endif
            DestroyWindow(Dialog);
            return TRUE;

        case WM_DESTROY:

            if (g_AppFont10)
                DeleteObject(g_AppFont10);
            return TRUE;
    }
    return FALSE;
}

/*//////////////////////////////////////////////////////////////////////////////
//
//  Keyboard Hook
*/

static HHOOK g_HookHandle;

LRESULT CALLBACK KeyboardProc(int Code, WPARAM wParam, LPARAM lParam)
{
    if ((Code >= 0) && (g_AppWindow != NULL))
    {
        switch (wParam)
        {
            case VK_ESCAPE:
                if (lParam < 0)  /* key up */
                    SendMessage(g_AppWindow, WM_CLOSE, 0, 0);
                break;

            #ifdef MOD_VERSION
            case VK_RETURN:
                if (!g_ModRunning)
                {
                    if (lParam >= 0)
                    {
                        g_RunSpacer = ((GetKeyState(VK_LSHIFT) < 0) || (GetKeyState(VK_RSHIFT) < 0));
                        StartSelectedMod(g_AppWindow);
                    }
                    return TRUE;
                }
                break;
            #endif
        }
    }
    return CallNextHookEx(g_HookHandle, Code, wParam, lParam);
}

/*//////////////////////////////////////////////////////////////////////////////
//
//  WinMain
*/

#ifdef __BORLANDC__
#pragma argsused
#endif
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    LPCTSTR Parameter;
    HANDLE Mutex = NULL;
    TCHAR MutexName[MAX_PATH];
    TCHAR FileName[MAX_PATH];
    DWORD LastError;
    TCHAR *StrPos;
	LPCTSTR Slash;
    BOOL Return;
    MSG Message;
/*FIXME: Localization */
	LPVOID MessageBuffer;
/**/

    #ifdef _MSC_VER
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(nCmdShow);
    #endif

    /* Init */
    InitCommonControls();
	LoadLibrary(TEXT("riched32.dll"));
	LoadLibrary(TEXT("riched20.dll"));

    #ifndef MOD_VERSION
	if( !LoadString(hInstance, IDS_ANSI, GUI_RTF_ANSI, MAXSTR) )
		lstrcpyn(GUI_RTF_ANSI, TEXT("\\ansi\\ansicpg1252\\deflang1033\\deff0{\\fonttbl{\\f0\\fcharset0 MS Shell Dlg;}}\\fs16\\pard\\qc"), MAXSTR);
    if( !LoadString(hInstance, IDS_VERS, GUI_INF_VERS, MAXSTR) )
		lstrcpyn(GUI_INF_VERS, TEXT("Version: "), MAXSTR);
    #endif

    /* Mutex */
    GetModuleFileName(NULL, MutexName, charof(MutexName));
	CharUpper(MutexName);
	StrPos = lstrend(MutexName);
	Slash = NULL;
	while (StrPos >= MutexName)
	{
		if (TBSL == *StrPos)
			*StrPos = TFSL;
		if ((NULL == Slash) && (TFSL == *StrPos))
		{
			*StrPos = TNUL;
			Slash = StrPos;
		}
        StrPos--;
    }
    while (!Mutex)
    {
        Mutex = CreateMutex(NULL, TRUE, MutexName);
        LastError = GetLastError();
        if (!Mutex)
        {
            if (LastError == ERROR_INVALID_HANDLE)
                lstrcat(MutexName, TEXT("_"));
            else
                break;
        }
        else if (LastError == ERROR_ALREADY_EXISTS)
        {
            CloseHandle(Mutex);
/*FIXME: Localization */
			if (!FindWindow(TEXT("#32770"), TEXT("GothicStarter")))
			{
				MessageBuffer = NULL;
				FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
					NULL, ERROR_SERVICE_ALREADY_RUNNING, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                    (LPTSTR) &MessageBuffer, 0, NULL );
				if (MessageBuffer)
				{
					MessageBox(NULL, MessageBuffer, TEXT("GothicStarter"), MB_OK | MB_ICONASTERISK); 
                    LocalFree(MessageBuffer);
				}
			}
/**/
			ExitProcess(1);
        }
    }

	/* Instance */
    g_AppInstance = hInstance;

    /* Directories */
    GetModuleFileName(NULL, FileName, charof(FileName));
/*FIXME: Win95 support * /
	GetLongPathName(FileName, FileName, charof(FileName));
/**/
	lstrcpy(g_AppDirectory, FileName);
    StrPos = lstrend(g_AppDirectory);
    while ((StrPos >= g_AppDirectory) && (*StrPos != TBSL) && (*StrPos != TFSL))
    {
        *StrPos = TNUL;
        StrPos--;
    }
    SetCurrentDirectory(g_AppDirectory);
    GetCurrentDirectory(charof(g_AppDirectory), g_AppDirectory);

	g_IsGothic1 = !FileExists(TEXT("Gothic2.exe"));

    if (*lstrend(g_AppDirectory) != TBSL)
        lstrcat(g_AppDirectory, SBSL);
    SetCurrentDirectory(TEXT(".."));
    GetCurrentDirectory(charof(g_RootDirectory), g_RootDirectory);
    if (*lstrend(g_RootDirectory) != TBSL)
        lstrcat(g_RootDirectory, SBSL);
    SetCurrentDirectory(g_AppDirectory);

    /* Command Line */
    #ifdef MOD_VERSION
    g_RunSpacer = FALSE;
    #endif
    g_AutoStart = FALSE;
    lstrcpy(g_AutoFocus, TEXT("GothicGame.ini"));
    if (lpCmdLine && *lpCmdLine)
    {
        Parameter = strstrx(lpCmdLine, TEXT("-game:"), -1);
        if (Parameter)
        {
            Parameter += 6;
            RtlSecureZeroMemory(&g_AutoFocus, sizeof(g_AutoFocus));
            for (StrPos = g_AutoFocus; *Parameter; StrPos++)
                if ((*Parameter == TSPC) || (*Parameter == TEXT('"')))
                    break;
                else
                    *StrPos = *Parameter++;
            if (!strstrx(g_AutoFocus, TEXT(".ini"), -1))
                lstrcat(g_AutoFocus, TEXT(".ini"));
        }
        g_AutoStart = (strstrx(lpCmdLine, TEXT("-start"), -1) != NULL);
        if (g_AutoStart)
        {
            strcpyx(FileName, g_AppDirectory, g_AutoFocus, NULL);
            if (!FileExists(FileName))
            {
                g_AutoStart = FALSE;
/*FIXME: Localization */
				MessageBuffer = NULL;
				FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
					NULL, ERROR_FILE_NOT_FOUND, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                    (LPTSTR) &MessageBuffer, 0, NULL );
				if (MessageBuffer)
				{
					MessageBox(NULL, MessageBuffer, NULL, MB_OK | MB_ICONERROR); 
                    LocalFree(MessageBuffer);
				}
/**/
			}
        }
        #ifdef MOD_VERSION
        g_RunSpacer = g_AutoStart && (strstrx(lpCmdLine, TEXT("-spacer"), -1) != NULL);
        #endif
    }
    g_AutoClose = g_AutoStart;

    /* Dialog */
    g_AppWindow = CreateDialog(g_AppInstance, MAKEINTRESOURCE(IDD_MAIN), NULL, DlgProc);
    if (g_AppWindow)
    {
        g_HookHandle = SetWindowsHookEx(WH_KEYBOARD, (HOOKPROC)KeyboardProc, g_AppInstance, GetCurrentThreadId());

        if (IsIconic(g_AppWindow) || IsZoomed(g_AppWindow))
        {
            #ifdef MOD_VERSION
            if (IsZoomed(g_AppWindow))
                ShowWindow(g_AppWindow, SW_RESTORE);
            #endif
            ShowWindow(g_AppWindow, SW_HIDE);
            ShowWindow(g_AppWindow, SW_SHOW);
        }

        /* Message Loop */
        while (0 != (Return = GetMessage(&Message, g_AppWindow, 0, 0)))
        {
            if (Return == -1)
                break;
            if (!IsDialogMessage(g_AppWindow, &Message))
            {
                TranslateMessage(&Message);
                DispatchMessage(&Message);
            }
        }

        if (g_HookHandle)
            UnhookWindowsHookEx(g_HookHandle);
    }
    if (Mutex)
        CloseHandle(Mutex);
    return 0;
}

/*//////////////////////////////////////////////////////////////////////////////
//
//  Entry Point
*/

#if defined(__MINGW32__)

void __cdecl mainCRTStartup(void)
{
    TCHAR *lpCmdLine = GetCommandLine();
    if (*lpCmdLine == '"')
    {
        while (*lpCmdLine && (*lpCmdLine != '"'))
            lpCmdLine++;
        if (*lpCmdLine == '"')
            lpCmdLine++;
    }
    else
        while (*lpCmdLine > ' ')
            lpCmdLine++;
    while (*lpCmdLine && (*lpCmdLine <= ' '))
        lpCmdLine++;

    ExitProcess(WinMain(GetModuleHandle(NULL), NULL, lpCmdLine, 0));
}

#endif /* __MINGW32__ */

/* THE END */
