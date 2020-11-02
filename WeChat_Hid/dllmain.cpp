// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"
#include <stdio.h>
#include "resource.h"
#include "WeChatInit.h"

WeChatInit WeChat;
HMODULE DlgHMODULE = NULL;

extern "C" __declspec(dllexport) void StartWachat(HMODULE hModule);
BOOL CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
		StartWachat(hModule);	
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

DWORD WINAPI ClientThread(LPVOID lpParam)
{
	DialogBox(
		DlgHMODULE,
		MAKEINTRESOURCE(IDD_DIALOG1),
		NULL,
		&DialogProc
	);

	return 0;
}

extern "C" __declspec(dllexport) void StartWachat(HMODULE hModule)
{
	DlgHMODULE = hModule;
	CreateThread(NULL, NULL, ClientThread, NULL, NULL, NULL);
}

BOOL CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		break;
	case WM_COMMAND:
		if (wParam == IDC_BUTTON_RED)
		{
			WeChat.Init();
			WeChat.GetWeChatOffset(hwndDlg);
		}

		if (wParam == IDC_BUTTON_WRITE)
		{

		}

		break;
	case WM_CLOSE:
		EndDialog(hwndDlg, NULL);
		break;
	default:
		break;
	}

	return FALSE;
}