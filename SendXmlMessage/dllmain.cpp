// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"
#include <Windows.h>
#include <stdio.h>
#include "resource.h"
#include "SendXmlMessage.h"

INT_PTR CALLBACK DialogProc(
	_In_ HWND   hwndDlg,
	_In_ UINT   uMsg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
);
VOID ThreadProcess(HMODULE hModule);

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProcess, hModule, NULL, 0);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}


VOID ThreadProcess(HMODULE hModule)
{
	DialogBox(hModule, MAKEINTRESOURCE(MAIN), NULL, &DialogProc);
}

INT_PTR CALLBACK DialogProc(
	_In_ HWND   hwndDlg,
	_In_ UINT   uMsg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
)
{
	wchar_t wxid[0x100] = { 0 };
	wchar_t fWxid[0x100] = { 0 };
	wchar_t title[0x100] = { 0 };
	wchar_t content[0x200] = { 0 };
	wchar_t pic[0x200] = {0};

	wchar_t setTitle[0x200] = { 0 };
	wchar_t setContent[0x200] = { 0 };
	wchar_t setWxid[0x200] = { 0 };
	wchar_t setPic[0x200] = {0};
	switch (uMsg)
	{
	case WM_INITDIALOG:
		swprintf_s(setTitle, L"xml发送call测试");
		swprintf_s(setContent, L"哈哈哈哈哈阿三撒飒飒撒飒飒飒飒");
		swprintf_s(setWxid, L"filehelper");
		swprintf_s(setPic, L"https://edu-image.nosdn.127.net/457c990f8db94c1ca0bf9173a58bd986.jpg?imageView&quality=100&crop=0_0_439_247&thumbnail=223y124");
		SetDlgItemText(hwndDlg, WXID, setWxid);
		SetDlgItemText(hwndDlg, TITLE, setTitle);
		SetDlgItemText(hwndDlg, CONTENT, setContent);
		SetDlgItemText(hwndDlg, PIC, setPic);
		break;
	case WM_CLOSE:
		EndDialog(hwndDlg,0);
		break;
	case WM_COMMAND:
		if (wParam == SEND_XML) {
			GetDlgItemText(hwndDlg, WXID, wxid, sizeof(wxid));
			GetDlgItemText(hwndDlg, TITLE, title, sizeof(title));
			GetDlgItemText(hwndDlg, CONTENT, content, sizeof(content));
			SendXmlCard(hwndDlg, wxid, content,title);
		}
		if (wParam == NEW_SEND_XML) {
			GetDlgItemText(hwndDlg, WXID, wxid, sizeof(wxid));
			GetDlgItemText(hwndDlg, TITLE, title, sizeof(title));
			GetDlgItemText(hwndDlg, CONTENT, content, sizeof(content));
			GetDlgItemText(hwndDlg, PIC, pic, sizeof(pic));
			swprintf_s(fWxid, L"hechongos");
			newXmlMessage(hwndDlg, wxid, fWxid, title, content, pic);
		}
		break;
	default:
		break;
	}
	return FALSE;
}