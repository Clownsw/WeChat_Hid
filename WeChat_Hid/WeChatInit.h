#pragma once

#include <Windows.h>

class WeChatInit
{
public:
	WeChatInit();

	VOID Init();
	DWORD GetWeChatWinAddr(void);
	VOID GetWeChatOffset(HWND hwndDlg);
private:
	HWND WeChatHWND;
	HANDLE WeChathProcess;
	DWORD WeChatPid;
};
