#include<Windows.h>
#include<tchar.h>
#include "resource.h"
#include "Anim.h"





LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
TCHAR WinName[] = _T("MainFrame");
HINSTANCE hInst;
int APIENTRY _tWinMain(HINSTANCE This, //Дескриптор текущего приложения
	HINSTANCE Prev, //В современных системах всегда 0
	LPTSTR cmd, //Командная строка
	int mode) //Режим отображения окна

{
	HWND hWnd; //Дескриптор главного окна программы
	MSG msg; //Структура для хранения сообщения
	hInst = This;
	WNDCLASS wc;//Класс окна
	//Определение класса окна
	wc.hInstance = This;
	wc.lpszClassName = WinName; //Имя класса окна
	wc.lpfnWndProc = WndProc; //Имя класса окна
	wc.style = CS_HREDRAW | CS_VREDRAW; //Стиль окна
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); //Стандартная иконка
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); //Стандартный курсор
	wc.lpszMenuName = NULL; //Нет меню
	wc.cbClsExtra = 0; //Нет дополнительных данных класса
	wc.cbWndExtra = 0; //Нет дополнительных данных окна
	//Заполнение окна белым цветом
	wc.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(255, 255, 255));
	if (!RegisterClass(&wc)) return 0;//Регистрация класса окна
	//Создание окна
	hWnd = CreateWindow(WinName,//Имя класса окна
		_T("Каркас Windows-приложения"),//Заголовок окна
		WS_OVERLAPPEDWINDOW, //Стиль окна
		CW_USEDEFAULT,//x
		CW_USEDEFAULT,//y Размеры окна
		CW_USEDEFAULT,//Width
		CW_USEDEFAULT,//Height
		HWND_DESKTOP,//Дескриптор родительской информации нет
		NULL,//Нет меню
		This,//Дескриптор приложения
		NULL);//Дополнительной информации нет
	ShowWindow(hWnd, mode);//Показать окно
	//Цикл обработки сообщений
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);//Функция трансляции кодов нажатой клавиши
		DispatchMessage(&msg);//Посылает сообщение функции WndProc()
	}
	return 0;

}
//Оконная функция вызывается операционной системой
//и получает сообщения из очереди для данного приложения
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	static ObjAnim arr[31];
	//static ObjAnim ship;
	//static ObjAnim Sea;
	static int caption, menu, border;
	static int t = 0;
	switch (message)
	{
	case WM_CREATE:
		SetTimer(hWnd, 10, 100, NULL);
		caption = GetSystemMetrics(SM_CYCAPTION);
		menu = GetSystemMetrics(SM_CYMENU);
		border = GetSystemMetrics(SM_CXFIXEDFRAME);
		hdc = GetDC(hWnd);
		arr[0] = ObjAnim(_T("1.bmp"), hdc);
		arr[1] = ObjAnim(_T("2.bmp"), hdc);
		arr[2] = ObjAnim(_T("3.bmp"), hdc);
		arr[3] = ObjAnim(_T("4.bmp"), hdc);
		arr[4] = ObjAnim(_T("5.bmp"), hdc);
		arr[5] = ObjAnim(_T("6.bmp"), hdc);
		arr[6] = ObjAnim(_T("7.bmp"), hdc);
		arr[7] = ObjAnim(_T("8.bmp"), hdc);
		arr[8] = ObjAnim(_T("9.bmp"), hdc);
		arr[9] = ObjAnim(_T("10.bmp"), hdc);
		arr[10] = ObjAnim(_T("11.bmp"), hdc);
		arr[11] = ObjAnim(_T("12.bmp"), hdc);
		arr[12] = ObjAnim(_T("13.bmp"), hdc);
		arr[13] = ObjAnim(_T("14.bmp"), hdc);
		arr[14] = ObjAnim(_T("15.bmp"), hdc);
		arr[15] = ObjAnim(_T("16.bmp"), hdc);
		arr[16] = ObjAnim(_T("17.bmp"), hdc);
		arr[17] = ObjAnim(_T("18.bmp"), hdc);
		arr[18] = ObjAnim(_T("19.bmp"), hdc);
		arr[19] = ObjAnim(_T("20.bmp"), hdc);
		arr[20] = ObjAnim(_T("21.bmp"), hdc);
		arr[21] = ObjAnim(_T("22.bmp"), hdc);
		arr[22] = ObjAnim(_T("23.bmp"), hdc);
		arr[23] = ObjAnim(_T("24.bmp"), hdc);
		arr[24] = ObjAnim(_T("25.bmp"), hdc);
		arr[25] = ObjAnim(_T("26.bmp"), hdc);
		arr[26] = ObjAnim(_T("27.bmp"), hdc);
		arr[27] = ObjAnim(_T("28.bmp"), hdc);
		arr[28] = ObjAnim(_T("29.bmp"), hdc);
		arr[29] = ObjAnim(_T("30.bmp"), hdc);
		arr[30] = ObjAnim(_T("31.bmp"), hdc);

		//ship = ObjAnim(_T("ship.bmp"), hdc);
		//Sea = ObjAnim(_T("Sea.bmp"), hdc);
		ReleaseDC(hWnd, hdc);
		break;
	case WM_TIMER:
		t++;
		//if (t > arr[0].bm.bmWidth) t = -1* arr[0].bm.bmWidth;
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_SIZE:
		MoveWindow(hWnd, 100, 50, arr[0].bm.bmWidth + 2 * border, arr[0].bm.bmHeight + caption
			+ menu + border, TRUE);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDM_EXIT: DestroyWindow(hWnd); break;
		default: DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		arr[t % 31].Draw(0, 0, hdc);
		//Sea.Draw(0, Sea.bm.bmHeight + caption + menu + border, hdc);
		//ship.Draw(t, 100, hdc);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:PostQuitMessage(0); break;
	default: return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}