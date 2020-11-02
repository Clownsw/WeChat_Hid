#include "pch.h"
#include "WeChatInit.h"
#include "resource.h"
#include <iostream>
#include <string>
#include <cstdio>

WeChatInit::WeChatInit()
{
	WeChatHWND = NULL;
	WeChathProcess = NULL;
	WeChatPid = NULL;
}

VOID WeChatInit::Init()
{
	WeChatHWND = FindWindow("WeChatMainWndForPC", "微信");
	GetWindowThreadProcessId(WeChatHWND, &WeChatPid);
	WeChathProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, WeChatPid);
}

DWORD WeChatInit::GetWeChatWinAddr(void)
{
	HANDLE dll_handle = LoadLibrary("WeChatWin.dll");
	return DWORD(dll_handle);
}

VOID WeChatInit::GetWeChatOffset(HWND hwndDlg)
{
	DWORD dll_addr = GetWeChatWinAddr();

	//微信ID
	char WXID[100]{};
	sprintf_s(WXID, "%s", (dll_addr + 0x1856BF0));
	SetDlgItemText(hwndDlg, IDC_EDIT_WXID, WXID);

	//微信账号
	char WX_username[100]{};
	sprintf_s(WX_username, "%s", (dll_addr + 0x1856AC0));
	SetDlgItemText(hwndDlg, IDC_EDIT_WXZH, WX_username);

	//微信头像
	char WX_Pic[200]{};
	DWORD temp = (dll_addr + 0x1856D54);
	sprintf_s(WX_Pic, "%s", (*(DWORD*)temp));
	SetDlgItemText(hwndDlg, IDC_EDIT_WXTX, WX_Pic);
}
