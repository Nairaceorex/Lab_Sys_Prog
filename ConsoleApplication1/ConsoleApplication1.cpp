#include <iostream>
#include <Windows.h>
using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    WIN32_FIND_DATAW findData;
    HANDLE hf;
    wstring s = L"C:\\*_??.??.????.csv";
    hf = FindFirstFileW(s.c_str(), &findData);

    if (hf == INVALID_HANDLE_VALUE)
    {
        cout << "Cannot find file" << endl;
        return -1;
    }
    int k = 0;
    do
    {
        if (findData.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE)
        {
            k++;
            cout << findData.cFileName << endl;
        }
    } while (FindNextFileW(hf, &findData));
    cout << k << endl;

    FindClose(hf);
    system("pause");
}