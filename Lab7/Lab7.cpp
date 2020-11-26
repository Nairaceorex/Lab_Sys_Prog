#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<Windowsx.h>
#include<tchar.h>
#define MoveTo(hdc, x, y) MoveToEx(hdc,x,y,NULL)
#define DIVISIONS 5


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ChildWndProc(HWND, UINT, WPARAM, LPARAM);
TCHAR szChildClass[] = _T("Checker_Child");

//==================================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	TCHAR szAppName[] = _T("Checker");
	HWND hMainWnd;
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
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szAppName;
	wc.hIconSm = LoadIcon(hInstance, szAppName);
	//Регистрируем класс окна
	RegisterClassEx(&wc);
	wc.lpfnWndProc = ChildWndProc;
	wc.cbWndExtra = sizeof(WORD);
	wc.hIcon = NULL;
	wc.lpszClassName = szChildClass;
	wc.hIconSm = NULL;
	if (!RegisterClassExW(&wc)) {
		MessageBoxW(NULL, _T("Cannot registr class"), _T("Error"), MB_OK);
		return 0;
	}
	//Создаем основное окно приложения
	hMainWnd = CreateWindow(szAppName, _T("A Hello1 Application"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL,
		hInstance, NULL);

	if (!hMainWnd) {
		MessageBox(NULL, _T("Cannot create main window"), _T("Error"), MB_OK);
		return 0;
	}

	//Показываем окно
	ShowWindow(hMainWnd, nCmdShow);
	UpdateWindow(hMainWnd);
	//Выполняем цикл обработки сообщений до закрытия окна
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
	return msg.wParam;

}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	static HWND hwndChild[DIVISIONS][DIVISIONS];
	int cxB, cyB, x, y;

	switch (uMsg) {
	case WM_CREATE:
		for (x = 0;x < DIVISIONS;x++)
			for (y = 0; y < DIVISIONS; y++) {
				hwndChild[x][y] = CreateWindow(szChildClass, NULL, WS_CHILDWINDOW | WS_VISIBLE, 0, 0, 0, 0, hWnd, (HMENU)(y << 8 | x), (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), NULL);
			}
		return 0;
	case WM_SIZE:
		cxB = LOWORD(lParam) / DIVISIONS;
		cyB = HIWORD(lParam) / DIVISIONS;
		for (x = 0; x < DIVISIONS; x++)
			for (y = 0; y < DIVISIONS; y++)
				MoveWindow(hwndChild[x][y], x * cxB, y * cyB, cxB, cyB, TRUE);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;

}
LRESULT CALLBACK ChildWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rect;
	switch (uMsg)
	{
	//case WM_CREATE:
		//SetWindowWord(hwnd, 0, 0);
		//return 0;
	case WM_LBUTTONDOWN:
		SetWindowWord(hwnd, 0, 1 ^ GetWindowWord(hwnd, 0));
		InvalidateRect(hwnd, NULL, FALSE);
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rect);
		Rectangle(hdc, 0, 0, rect.right, rect.bottom);
		if (GetWindowWord(hwnd, 0)) {
			MoveTo(hdc, 0, 0);
			LineTo(hdc, rect.right, rect.bottom);
			MoveTo(hdc, 0, rect.bottom);
			LineTo(hdc, rect.right, 0);
		}
		EndPaint(hwnd, &ps);
		return 0;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);

}