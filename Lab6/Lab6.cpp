#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<tchar.h>
#include "Resource.h"
#define ID_STDDIALOG 11
#define IDC_HSCR -1
#define IDC_VSCR -2
INT_PTR CALLBACK Dialog1(HWND, UINT, WPARAM, LPARAM);

LPCWSTR combo[] = { _T("aa"),_T("bb"),_T("cc") };
TCHAR WinName[] = _T("MainFrame");
HINSTANCE hInst;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	HWND hwnd;
	MSG msg;
	WNDCLASSEX wc;
	hInst = hInstance;
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WinName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	//Регистрируем класс окна
	if (!RegisterClassEx(&wc)) return 0;
	hwnd = CreateWindow(WinName, _T("Dialog"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT,
		HWND_DESKTOP, NULL, hInstance, NULL);
	//Показываем окно
	ShowWindow(hwnd, nCmdShow);

	//UpdateWindow(hMainWnd);
	//Выполняем цикл обработки сообщений до закрытия окна
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
	return 0;

}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR str[256];
	int i;
	HMENU hMenu, hPopupMenu;
	TCHAR str0[] = _T("Диалог");
	TCHAR str1[] = _T("Открыть");
	switch (uMsg) {
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case ID_STDDIALOG:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, Dialog1);
			return 0;
		default: return DefWindowProc(hWnd, uMsg, wParam, lParam);
		}
		break;
	case WM_CREATE:
		hMenu = CreateMenu();
		hPopupMenu = CreatePopupMenu();
		AppendMenu(hPopupMenu, MF_STRING, ID_STDDIALOG, str1);
		AppendMenu(hMenu, MF_POPUP, (UINT)hPopupMenu, str0);
		SetMenu(hWnd, hMenu);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

INT_PTR CALLBACK Dialog1(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HBRUSH hBrushBk = CreateSolidBrush(RGB(149, 123, 141));
	HBRUSH hBrushStatic = CreateSolidBrush(RGB(149, 123, 141));
	static HWND hWndComboBox;
	TCHAR arr[] = _T("*.exe");
	HDC hdc;
	switch (uMsg) {
	case WM_INITDIALOG:
		DlgDirListComboBox(hDlg, arr, IDC_COMBO1, IDC_STATIC,
			DDL_READWRITE | DDL_READONLY | DDL_HIDDEN |
			DDL_SYSTEM | DDL_DIRECTORY | DDL_DRIVES |
			DDL_ARCHIVE);
		return TRUE;
		
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON1: return EndDialog(hDlg, 0);
		case IDCANCEL: return EndDialog(hDlg, 0);
		}
		return TRUE;
	case WM_CTLCOLORDLG: return (LONG)hBrushBk;
	case WM_CTLCOLORSTATIC:
		hdc = (HDC)wParam;
		SetTextColor(hdc, RGB(148, 0, 211));
		return (LONG)hBrushStatic;
	
		
	case WM_ERASEBKGND:
		break;
	default: return FALSE;
	}
	return FALSE;
}

