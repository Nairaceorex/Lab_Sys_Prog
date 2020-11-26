#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<tchar.h>
#include<string.h>
#include"Lab4.h"
HMENU hmenu, hpopup, hpopup2;
char szAppName[] = "calendar";
HWND hCB, hLB, hCY, hE, hT;
char Buf1[80], Buf[80];
HINSTANCE hInstance;
HBRUSH hbrush;
HDC hdc1, memdc;
PAINTSTRUCT ps;
LPSTR ReturnDate(int day, int month, int year);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	HWND hWnd;
	WNDCLASSEX wc;
	MSG msg;
	ZeroMemory(&wc, sizeof(wc));
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDC_ARROW);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = 0;
	wc.lpszClassName = szAppName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	if (!RegisterClassEx(&wc)) return FALSE;

	hWnd = CreateWindow(szAppName, "CALENDAR", WS_OVERLAPPEDWINDOW, 100, 100, 300, 530, (HWND)NULL, (HMENU)NULL,
		hInstance, (LPSTR)NULL);
	if (!hWnd) return FALSE;
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
	return ((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	static HWND hwnded;
	int i;
	static int k = 0;
	int maxx = 0, maxy = 0;
	char day[10];
	HBITMAP hbit;
	switch (uMsg) {
	case WM_CREATE:
		hdc1 = GetDC(hwnd);
		maxy = GetSystemMetrics(SM_CXSCREEN);
		maxy = GetSystemMetrics(SM_CXSCREEN);
		hCB = CreateWindow("ComboBox", NULL, WS_CHILD | WS_VISIBLE | WS_VSCROLL | CBS_DROPDOWNLIST | CBS_HASSTRINGS, 90, 80, 100, 200, hwnd, (HMENU)ID_COMBODAY, hInstance, NULL);
		//hT = CreateWindow("Button", "Выбрать", WS_CHILD | WS_VISIBLE, 90, 415, 100, 27, hwnd, (HMENU)ID_TAKE, hInstance, NULL);
		//hE = CreateWindow("Button", "Выход", WS_CHILD | WS_VISIBLE, 90, 450, 100, 27, hwnd, (HMENU)ID_EXIT, hInstance, NULL);
		for (i = 10; i < 54; i++)
		{
			_itoa(i, day, 10);
			SendMessage(hCB, CB_ADDSTRING, 0, (LPARAM)day);
		}
		memdc = CreateCompatibleDC(hdc1);
		hbit = CreateCompatibleBitmap(hdc1, maxx, maxy);
		SelectObject(memdc, hbit);
		break;
	case WM_SIZE:
		InvalidateRect(hwnd, NULL, 1);
		break;
	case WM_PAINT:
		hdc1 = BeginPaint(hwnd, &ps);
		SetTextColor(hdc1, RGB(255, 255, 67));
		SetBkMode(hdc1, TRANSPARENT);
		_itoa(k, day, 10);
		TextOut(hdc1, 85, 60, day, strlen(day));
		memdc = CreateCompatibleDC(hdc1);
		BitBlt(hdc1, 0, 0, maxx, maxy, memdc, 0, 0, SRCCOPY);
		EndPaint(hwnd, &ps);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_COMBODAY:
			if (HIWORD(wParam)== CBN_SELENDOK) {
				k = SendMessage(hCB, CB_GETCURSEL, 0, 0L) + 1;
				InvalidateRect(hwnd, NULL, TRUE);
			}
			break;
		
		}

		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}