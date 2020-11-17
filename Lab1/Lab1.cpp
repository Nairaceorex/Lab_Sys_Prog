#define _CRT_SECURE_NO_WORNINGS
#include<Windows.h>
#include<tchar.h>
#include <stdlib.h>
#include <ctime>
#include <windowsx.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void DrawRectangle(HWND hwnd);
int cx, cy;
HBRUSH hPurpleBrush, hBlueBrush, hDBlueBrush;
//==================================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	HWND hMainWnd;
	TCHAR szClassName[] = _T("MyClass");
	MSG msg;
	WNDCLASSEX wc;
	//Заполняем структуру класса окна
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szClassName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	//Регистрируем класс окна
	if (!RegisterClassExW(&wc)) {
		MessageBoxW(NULL, _T("Cannot registr class"), _T("Error"), MB_OK);
		return 0;
	}
	//Создаем основное окно приложения
	hMainWnd = CreateWindow(szClassName, _T("A Hello1 Application"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL,
		hInstance, NULL);

	if (!hMainWnd) {
		MessageBox(NULL, _T("Cannot create main window"), _T("Error"), MB_OK);
		return 0;
	}
	//Показываем окно
	ShowWindow(hMainWnd, nCmdShow);
	//UpdateWindow(hMainWnd);
	//Выполняем цикл обработки сообщений до закрытия окна
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
	return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam,
	LPARAM lParam) {
	static POINT apt[4];
	HDC hdc;
	static int t;

	PAINTSTRUCT ps;
	switch (uMsg) {
	case WM_CREATE:
		hPurpleBrush = CreateSolidBrush(RGB(255, 0, 255));
		hBlueBrush = CreateSolidBrush(RGB(0, 0, 255));
		hDBlueBrush = CreateSolidBrush(RGB(0, 33, 55));
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		SelectBrush(hdc, hPurpleBrush);
		Rectangle(hdc, 0, 0, 300, 300);
		SelectBrush(hdc, hBlueBrush);
		Rectangle(hdc, 0, 0, 200, 200);
		SelectBrush(hdc, hDBlueBrush);
		Rectangle(hdc, 0, 0, 100, 100);
		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

