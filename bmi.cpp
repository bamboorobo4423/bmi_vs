#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include "resource.h"
#include <stdio.h>

LPCTSTR doLoadString(INT nID)
{
    static TCHAR s_szText[MAX_PATH];
    s_szText[0] = 0;
    LoadString(NULL, nID, s_szText, _countof(s_szText));
    return s_szText;
}

//自作ヘルパー関数1(GetDlgItemInt)
//

//
BOOL getDlgItemDouble(
	HWND hwnd,
	int nIDDlgItem,
	double *peValue)//結果を受け取りたい
{
    char str[30];
    LONG_PTR result = 0;
    LPSTR   lpString ="";

    GetDlgItemTextA(hwnd,nIDDlgItem, str, sizeof(str));

	*peValue = atof(str);
	return 1;
}


//自作ヘルパー関数2(setDlgItemDouble)
BOOL setDlgItemDouble(
	HWND hwnd,
	int nIDDlgItem,
	double eValue)//渡したい
{
	char str[20];
	sprintf( str, "%lf", eValue );//sprintf入ってないって怒られた
	SendDlgItemMessageA( hwnd, nIDDlgItem, WM_SETTEXT, 0, (LPARAM)str );
	return TRUE;
}


void OnPsh1(HWND hwnd)
{
	double weight,height;
    if (!getDlgItemDouble(hwnd, edt1, &height))
    {
    	DebugBreak();
        SetDlgItemText(hwnd, edt3, doLoadString(IDS_ERROR));

    }
    if (!getDlgItemDouble(hwnd, edt2, &weight))
    {
    	DebugBreak();
        SetDlgItemText(hwnd, edt3, doLoadString(IDS_ERROR));

    }
    double bmi = weight / ((height *0.01) * (height * 0.01));
    setDlgItemDouble(hwnd, edt3, bmi);
}

// EN_CHANGE
BOOL OnChange(HWND hwnd)
{
    double weight, height;
    if (!getDlgItemDouble(hwnd, edt1, &height))
    {
        DebugBreak();
        SetDlgItemText(hwnd, edt3, doLoadString(IDS_ERROR));
        return false;
    }
    if (!getDlgItemDouble(hwnd, edt2, &weight))
    {
        DebugBreak();
        SetDlgItemText(hwnd, edt3, doLoadString(IDS_ERROR));
        return false;
    }
    double bmi = weight / ((height * 0.01) * (height * 0.01));
    setDlgItemDouble(hwnd, edt3, bmi);
    return TRUE;
}

BOOL OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
    SetDlgItemInt(hwnd, edt1, 1, TRUE);
    SetDlgItemInt(hwnd, edt2, 2, TRUE);
    return TRUE;
}

void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
    switch (id)
    {
    case IDOK:
    case IDCANCEL:
        EndDialog(hwnd, id);
        break;
    case edt1:
    case edt2:
       // if (codeNotify == EN_CHANGE)
       // {
       //     OnChange(hwnd);
       // }
        break;
    case psh1:
        OnPsh1(hwnd);
    	break;
    }
}

INT_PTR CALLBACK
DialogProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        HANDLE_MSG(hwnd, WM_INITDIALOG, OnInitDialog);
        HANDLE_MSG(hwnd, WM_COMMAND, OnCommand);
    }
    return 0;
}

INT WINAPI
WinMain(HINSTANCE   hInstance,
        HINSTANCE   hPrevInstance,
        LPSTR       lpCmdLine,
        INT         nCmdShow)
{
    InitCommonControls();
    DialogBox(hInstance, MAKEINTRESOURCE(IDD_MAIN), NULL, DialogProc);
    return 0;
}
