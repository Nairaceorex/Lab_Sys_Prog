#include<Windows.h>
#include<tchar.h>

class ObjAnim {
public:
	HBITMAP hBitmap;
	HDC memBit;
	BITMAP bm;
	ObjAnim() {}

	ObjAnim(LPCWSTR name, HDC hdc)
	{
		this->hBitmap = (HBITMAP)LoadImage(NULL, name, IMAGE_BITMAP,
			0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		GetObject(hBitmap, sizeof(bm), &bm);
		memBit = CreateCompatibleDC(hdc);
		SelectObject(memBit, hBitmap);
	}

	void Create(LPCWSTR name, HDC hdc) {
		this->hBitmap = (HBITMAP)LoadImage(NULL, name, IMAGE_BITMAP,
			0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		GetObject(hBitmap, sizeof(bm), &bm);
		memBit = CreateCompatibleDC(hdc);
		SelectObject(memBit, hBitmap);
	}

	void Draw(int x, int y, HDC hdc) {
		BitBlt(hdc, 0 + x, 0 + y, bm.bmWidth, bm.bmHeight, memBit, 0, 0, SRCCOPY);
	}

};
