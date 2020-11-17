#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<tchar.h>
#include<string.h>
#include"Lab4.h"
HMENU hmenu, hpopup, hpopup2;
char szAppName[] = _T("calendar");
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
	int date, month, year;
	int maxx = 0, maxy = 0;
	char day[2];
	HBITMAP hbit;
	switch (uMsg) {
	case WM_CREATE:
		hdc1 = GetDC(hwnd);
		maxy = GetSystemMetrics(SM_CXSCREEN);
		maxy = GetSystemMetrics(SM_CXSCREEN);
		hCB = CreateWindow("ComboBox", NULL, WS_CHILD | WS_VISIBLE | WS_VSCROLL | CBS_DROPDOWNLIST | CBS_HASSTRINGS, 90, 80, 100, 200, hwnd, (HMENU)ID_COMBODAY, hInstance, NULL);
		hT = CreateWindow("Button", "Выбрать", WS_CHILD | WS_VISIBLE, 90, 415, 100, 27, hwnd, (HMENU)ID_TAKE, hInstance, NULL);
		hE = CreateWindow("Button", "Выход", WS_CHILD | WS_VISIBLE, 90, 450, 100, 27, hwnd, (HMENU)ID_EXIT, hInstance, NULL);
		for (i = 1; i < 52; i++)
		{
			_itoa(i, day, 10);
			SendMessage(hCB, CB_ADDSTRING, 1, (LPARAM)day);
		}
		SendMessage(hCB, CB_SETCURSEL, 0, 0L);



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
		TextOut(hdc1, 85, 60, "Выберете число: ", 16);
		memdc = CreateCompatibleDC(hdc1);
		BitBlt(hdc1, 0, 0, maxx, maxy, memdc, 0, 0, SRCCOPY);
		EndPaint(hwnd, &ps);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_EXIT:
			DestroyWindow(hwnd);
			break;
		case ID_TAKE:
			date = SendMessage(hCB, CB_GETCURSEL, 0, 0L);
			month = SendMessage(hLB, LB_GETCURSEL, 0, 0L);
			year = SendMessage(hCY, CB_GETCURSEL, 0, 0L);
			SendMessage(hCY, CB_GETLBTEXT, (WPARAM)year, (LPARAM)Buf1);
			lstrcpy(Buf, ReturnDate(date, month, atoi(Buf1)));
			MessageBox(NULL, Buf, _T(""), MB_OK);
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
LPSTR ReturnDate(int day, int month, int year) {
	char myDay[80] = "";
	_itoa(day + 1, myDay, 10);
	lstrcat(myDay, "-я строка ");

	//Конкатенируем с годом

	//Возвращаем готовую дату
	return myDay;
}