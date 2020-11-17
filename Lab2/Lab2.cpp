#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<tchar.h>
#include<cmath>
#include "Lab2.h"
#include <windowsx.h>
HBRUSH hBlueBrush, hGreenBrush, hRedBrush, hYellowBrush;
HPEN hBluePen, hRedPen;
int sw;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	HWND hMainWnd;
	TCHAR szClassName[] = _T("menudemo");
	MSG msg;
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(wc));
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = _T("menudemo");
	wc.lpszClassName = szClassName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	if (!RegisterClassExW(&wc)) {
		MessageBoxW(NULL, _T("Cannot registr class"), _T("Error"), MB_OK);
		return 0;
	}
	hMainWnd = CreateWindow(szClassName, _T("menudemo"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL,
		hInstance, NULL);

	if (!hMainWnd) {
		MessageBox(NULL, _T("Cannot create main window"), _T("Error"), MB_OK);
		return 0;
	}
	ShowWindow(hMainWnd, nCmdShow);
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
	return 0;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	HDC hdc;
	PAINTSTRUCT ps;
	HMENU hMenu, hPopupMenu;
	TCHAR str0[] = _T("Отражение");
	TCHAR str1[] = _T("Справа");
	TCHAR str2[] = _T("Слева");
	switch (uMsg) {
	case WM_COMMAND:
		hMenu = GetMenu(hWnd);
		switch (LOWORD(wParam))
		{
		case MI_RIGHT:
			sw = 1;
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case MI_LEFT:
			sw = 2;
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case MI_EXIT:
			DestroyWindow(hWnd);
		}
		break;
	case WM_CREATE:
		hBlueBrush = CreateSolidBrush(RGB(200, 200, 200));
		hGreenBrush = CreateSolidBrush(RGB(200, 200, 200));
		hMenu = CreateMenu();
		hPopupMenu = CreatePopupMenu();
		AppendMenu(hPopupMenu, MF_STRING, MI_RIGHT, str1);
		AppendMenu(hPopupMenu, MF_STRING, MI_LEFT, str2);



		AppendMenu(hMenu, MF_POPUP, (UINT)hPopupMenu, str0);
		SetMenu(hWnd, hMenu);
		break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		Ellipse(hdc, 250, 250, 450, 450);
		if (sw == 2)
		{
			SelectBrush(hdc, hGreenBrush);
			Pie(hdc, 250, 250, 450, 450, 350, 250, 350, 450);
		}
		if (sw == 1)
		{
			SelectBrush(hdc, hBlueBrush);
			Pie(hdc, 250, 250, 450, 450, 350, 450, 350, 250);
		}

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;

}