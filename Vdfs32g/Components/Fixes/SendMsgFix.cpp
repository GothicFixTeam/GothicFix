#include "PreCompiled.h"

LRESULT WINAPI MySendMessageA(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	if(hWnd == HWND_BROADCAST)
		return SendMessageTimeoutA(hWnd, Msg, wParam, lParam, SMTO_BLOCK, 100, NULL);
	return SendMessageA(hWnd, Msg, wParam, lParam);
}

bool InstallSendMsgFix(void)
{
	uChar* codeBase = (uChar*)GetModuleHandle(NULL);
	PIMAGE_IMPORT_DESCRIPTOR importDesc = GetImportDescriptor(codeBase, "USER32.dll");
	if(importDesc)
		PatchImportFunctionAddress<FARPROC>(codeBase, importDesc, false, "SendMessageA", (FARPROC)MySendMessageA);
	return true;
}

void RemoveSendMsgFix(void)
{
}