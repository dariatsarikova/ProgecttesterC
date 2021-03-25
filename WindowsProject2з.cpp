#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NON_CONFORMING_SWPRINTFS
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <Shlwapi.h>
#include <iostream>
#include <stack>
#include <cctype>
#include <map>
#include <string>
#include <cstdio>
#include <sstream>
#include <windows.h>
#pragma comment (lib, "Shlwapi.lib")

static TCHAR szWindowClass[] = _T("win32app");
static TCHAR szTitle[] = _T("Калькулятор");
TCHAR buf[256];

HINSTANCE hInst;
TCHAR* Calculate(TCHAR* buf);

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// Главная часть программы-------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow)
{
    // ------------------------------------------------------------------------------------------------------------

    // Структура класса окна---------------------------------------------------------------------------------------
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 11);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);
    // ------------------------------------------------------------------------------------------------------------

    // Регистрируем класс окна------------------------------------------------------------------------------------
    if (!RegisterClassEx(&wcex))
    {
        MessageBox(NULL,
            _T("Call to RegisterClassEx failed!"),
            _T("Win32 Guided Tour"),
            0);
        return 1;
    }
    // ------------------------------------------------------------------------------------------------------------

    // Создаём окно---------------------------------------------------------------------------------------
    hInst = hInstance;

    HWND hWnd = CreateWindow(
        szWindowClass,
        szTitle,
        WS_SYSMENU,
        CW_USEDEFAULT, CW_USEDEFAULT,
        480, 220,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (!hWnd)
    {
        MessageBox(NULL,
            _T("Call to CreateWindow failed!"),
            _T("Win32 Guided Tour"),
            0);
        return 1;
    }
    // ------------------------------------------------------------------------------------------------------------

    // Отображаем окно---------------------------------------------------------------------------------------------
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    // ------------------------------------------------------------------------------------------------------------

    // Цикл обработки сообщений для прослушивания отправляемых ОС сообщений----------------------------------------
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}
// ------------------------------------------------------------------------------------------------------------

// Функция------------------------------------------------------------------------------------------------------------
#define ID_EDIT  99
#define ID_BUTTON    100
#define ID_BUTTON_1  101
#define ID_BUTTON_2  102
#define ID_BUTTON_3  103
#define ID_BUTTON_4  104
#define ID_BUTTON_5  105
#define ID_BUTTON_6  106
#define ID_BUTTON_7  107
#define ID_BUTTON_8  108
#define ID_BUTTON_9  109
#define ID_BUTTON_ADD    110
#define ID_BUTTON_SUB    111
#define ID_BUTTON_MUL    112
#define ID_BUTTON_DIV    113
#define ID_BUTTON_RES   114
#define ID_BUTTON_C    115
#define ID_BUTTON_del  116
#define ID_BUTTON_MIN  117
#define ID_BUTTON_dr  118
#define ID_BUTTON_kor  119

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    // Структура класса кнопки-------------------------------------------------------------------------------------
    static HWND hButton[20], hEdit, hListBox;
    PAINTSTRUCT ps;
    HDC hdc;
    int i = 0;
    int count = 0, a = 0, b = 0;
    // ------------------------------------------------------------------------------------------------------------
    switch (message)
    {
    case WM_CREATE:
        hEdit = CreateWindow(_T("edit"), _T("0"), WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT, 10, 5, 400, 35, hWnd, (HMENU)ID_EDIT, hInst, 0);
        hButton[0] = CreateWindow(_T("Button"), _T("0"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 150, 130, 30, hWnd, (HMENU)ID_BUTTON, hInst, 0);
        hButton[1] = CreateWindow(_T("Button"), _T("1"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 115, 40, 30, hWnd, (HMENU)ID_BUTTON_1, hInst, 0);
        hButton[2] = CreateWindow(_T("Button"), _T("2"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 55, 115, 40, 30, hWnd, (HMENU)ID_BUTTON_2, hInst, 0);
        hButton[3] = CreateWindow(_T("Button"), _T("3"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 100, 115, 40, 30, hWnd, (HMENU)ID_BUTTON_3, hInst, 0);
        hButton[4] = CreateWindow(_T("Button"), _T("4"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 80, 40, 30, hWnd, (HMENU)ID_BUTTON_4, hInst, 0);
        hButton[5] = CreateWindow(_T("Button"), _T("5"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 55, 80, 40, 30, hWnd, (HMENU)ID_BUTTON_5, hInst, 0);
        hButton[6] = CreateWindow(_T("Button"), _T("6"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 100, 80, 40, 30, hWnd, (HMENU)ID_BUTTON_6, hInst, 0);
        hButton[7] = CreateWindow(_T("Button"), _T("7"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 45, 40, 30, hWnd, (HMENU)ID_BUTTON_7, hInst, 0);
        hButton[8] = CreateWindow(_T("Button"), _T("8"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 55, 45, 40, 30, hWnd, (HMENU)ID_BUTTON_8, hInst, 0);
        hButton[9] = CreateWindow(_T("Button"), _T("9"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 100, 45, 40, 30, hWnd, (HMENU)ID_BUTTON_9, hInst, 0);
        hButton[10] = CreateWindow(_T("Button"), _T("+"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 150, 80, 43, 30, hWnd, (HMENU)ID_BUTTON_ADD, hInst, 0);
        hButton[11] = CreateWindow(_T("Button"), _T("-"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 196, 80, 43, 30, hWnd, (HMENU)ID_BUTTON_SUB, hInst, 0);
        hButton[12] = CreateWindow(_T("Button"), _T("*"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 150, 115, 43, 30, hWnd, (HMENU)ID_BUTTON_MUL, hInst, 0);
        hButton[13] = CreateWindow(_T("Button"), _T("/"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 196, 115, 43, 30, hWnd, (HMENU)ID_BUTTON_DIV, hInst, 0);
        hButton[14] = CreateWindow(_T("Button"), _T("="), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 150, 150, 90, 30, hWnd, (HMENU)ID_BUTTON_RES, hInst, 0);
        hButton[15] = CreateWindow(_T("Button"), _T("C"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 365, 45, 90, 30, hWnd, (HMENU)ID_BUTTON_C, hInst, 0);
        hButton[16] = CreateWindow(_T("Button"), _T("^2"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 150, 45, 40, 30, hWnd, (HMENU)ID_BUTTON_del, hInst, 0);
        hButton[17] = CreateWindow(_T("Button"), _T("(-1)"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 196, 45, 43, 30, hWnd, (HMENU)ID_BUTTON_MIN, hInst, 0);
        hButton[18] = CreateWindow(_T("Button"), _T("sqrt"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 243, 45, 43, 30, hWnd, (HMENU)ID_BUTTON_kor, hInst, 0);
        hButton[19] = CreateWindow(_T("Button"), _T("1/x"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 290, 45, 40, 30, hWnd, (HMENU)ID_BUTTON_dr, hInst, 0);
        break;
    case WM_COMMAND:
        if ((LOWORD(wParam) == ID_BUTTON) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit, buf, sizeof(buf));
            if (*buf == TEXT('0') && 0 == buf[1]) *buf = 0;
            StrCat(buf, TEXT("0"));
            SetWindowText(hEdit, buf);
        }

        if ((LOWORD(wParam) == ID_BUTTON_1) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit, buf, sizeof(buf));
            if (*buf == TEXT('0') && 0 == buf[1]) *buf = 0;
            StrCat(buf, TEXT("1"));
            SetWindowText(hEdit, buf);
        }

        if ((LOWORD(wParam) == ID_BUTTON_2) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit, buf, sizeof(buf));
            if (*buf == '0' && 0 == buf[1]) *buf = 0;
            StrCat(buf, TEXT("2"));
            SetWindowText(hEdit, buf);
        }

        if ((LOWORD(wParam) == ID_BUTTON_3) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit, buf, sizeof(buf));
            if (*buf == '0' && 0 == buf[1]) *buf = 0;
            StrCat(buf, TEXT("3"));
            SetWindowText(hEdit, buf);
        }

        if ((LOWORD(wParam) == ID_BUTTON_4) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit, buf, sizeof(buf));
            if (*buf == '0' && 0 == buf[1]) *buf = 0;
            StrCat(buf, TEXT("4"));
            SetWindowText(hEdit, buf);
        }

        if ((LOWORD(wParam) == ID_BUTTON_5) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit, buf, sizeof(buf));
            if (*buf == '0' && 0 == buf[1]) *buf = 0;
            StrCat(buf, TEXT("5"));
            SetWindowText(hEdit, buf);
        }

        if ((LOWORD(wParam) == ID_BUTTON_6) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit, buf, sizeof(buf));
            if (*buf == '0' && 0 == buf[1]) *buf = 0;
            StrCat(buf, TEXT("6"));
            SetWindowText(hEdit, buf);
        }

        if ((LOWORD(wParam) == ID_BUTTON_7) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit, buf, sizeof(buf));
            if (*buf == '0' && 0 == buf[1]) *buf = 0;
            StrCat(buf, TEXT("7"));
            SetWindowText(hEdit, buf);
        }

        if ((LOWORD(wParam) == ID_BUTTON_8) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit, buf, sizeof(buf));
            if (*buf == '0' && 0 == buf[1]) *buf = 0;
            StrCat(buf, TEXT("8"));
            SetWindowText(hEdit, buf);
        }

        if ((LOWORD(wParam) == ID_BUTTON_9) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit, buf, sizeof(buf));
            if (*buf == '0' && 0 == buf[1]) *buf = 0;
            StrCat(buf, TEXT("9"));
            SetWindowText(hEdit, buf);
        }

        if ((LOWORD(wParam) == ID_BUTTON_ADD) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit, buf, sizeof(buf));
            StrCat(buf, TEXT("+"));
            SetWindowText(hEdit, buf);
        }

        if ((LOWORD(wParam) == ID_BUTTON_SUB) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit, buf, sizeof(buf));
            StrCat(buf, TEXT("-"));
            SetWindowText(hEdit, buf);
        }

        if ((LOWORD(wParam) == ID_BUTTON_MUL) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit, buf, sizeof(buf));
            StrCat(buf, TEXT("*"));
            SetWindowText(hEdit, buf);
        }

        if ((LOWORD(wParam) == ID_BUTTON_DIV) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit, buf, sizeof(buf));
            StrCat(buf, TEXT("/"));
            SetWindowText(hEdit, buf);
        }

        if ((LOWORD(wParam) == ID_BUTTON_RES) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit, buf, sizeof(buf));
            SetWindowText(hEdit, Calculate(buf));
        }

        if ((LOWORD(wParam) == ID_BUTTON_C) && (HIWORD(wParam) == BN_CLICKED))
        {
            SetWindowText(hEdit, TEXT("0"));
            buf[0] = 0;
        }

        if ((LOWORD(wParam) == ID_BUTTON_del) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit, buf, sizeof(buf));
            StrCat(buf, TEXT("^2"));
            SetWindowText(hEdit, buf);
        }
        if ((LOWORD(wParam) == ID_BUTTON_MIN) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit, buf, sizeof(buf));
            StrCat(buf, TEXT("(-1)"));
            SetWindowText(hEdit, buf);
        }
        if ((LOWORD(wParam) == ID_BUTTON_dr) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit, buf, sizeof(buf));
            StrCat(buf, TEXT("1/x"));
            SetWindowText(hEdit, buf);
        }
        if ((LOWORD(wParam) == ID_BUTTON_kor) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit, buf, sizeof(buf));
            StrCat(buf, TEXT("sqrt"));
            SetWindowText(hEdit, buf);
        }
        break;
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }
    return 0;
}

TCHAR* Calculate(TCHAR* buf)
{
    std::basic_string<TCHAR> s(buf), srpn, sres;
    std::basic_string<TCHAR>::size_type ind;
    while ((ind = s.find(TEXT(' '))) != std::basic_string<TCHAR>::npos) // удаление пробелов из входной строки
    {
        s.erase(ind, 1);
    }
    std::map<TCHAR, size_t> map; // карата весов символов
    map.insert(std::make_pair(TEXT('*'), 3));
    map.insert(std::make_pair(TEXT('/'), 3));
    map.insert(std::make_pair(TEXT('^2'), 2));
    map.insert(std::make_pair(TEXT('sqrt'), 2));
    map.insert(std::make_pair(TEXT('1/x'), 2));
    map.insert(std::make_pair(TEXT('(-1)'), 2));
    map.insert(std::make_pair(TEXT('+'), 2));
    map.insert(std::make_pair(TEXT('-'), 2));
    map.insert(std::make_pair(TEXT('('), 1));
    std::stack<TCHAR> stack;
    for (std::basic_string<TCHAR>::iterator ib = s.begin(); ib != s.end(); ++ib) // формировка результирующей строки в ОПЗ
    {
        if (!isdigit(*ib) && (TEXT('.') != *ib) && !(s.begin() == ib && '-' == *ib))
        {
            srpn += TEXT(' ');
            if (TEXT(')') == *ib)
            {
                while (stack.top() != TEXT('('))
                {
                    srpn += stack.top();
                    stack.pop();
                    srpn += TEXT(' ');
                }
                stack.pop();
            }
            else if (TEXT('(') == *ib)
            {
                stack.push(*ib);
            }
            else if (stack.empty() || (map[stack.top()] < map[*ib]))
            {
                stack.push(*ib);
            }
            else
            {
                do
                {
                    srpn += stack.top();
                    srpn += TEXT(' ');
                    stack.pop();
                } while (!(stack.empty() || (map[stack.top()] < map[*ib])));
                stack.push(*ib);
            }
        }
        else
        {
            srpn += *ib;
        }
    }
    while (!stack.empty())// остаток из стека добавляется в результ. строку
    {
        srpn += stack.top();
        srpn += TEXT(' ');
        stack.pop();
    }
    std::stack<double> dstack;
    std::basic_stringstream<TCHAR> ss(srpn);
    double d, d1,r=1.0;
    TCHAR c;
    while (ss.get(c)) // вычисление результата
    {
        if (isdigit(c) || TEXT('.') == c || (1 == ss.tellg() && TEXT('-') == c))
        {
            ss.unget();
            ss >> d;
            dstack.push(d);
        }
        else if (!isspace(c))
        {
            d1 = dstack.top();
            dstack.pop();
            d = dstack.top();
            dstack.pop();
            switch (c)
            {
            case TEXT('+'):
                dstack.push(d + d1);
                break;
            case TEXT('-'):
                dstack.push(d - d1);
                break;
            case TEXT('*'):
                dstack.push(d * d1);
                break;
            case TEXT('/'):
                dstack.push(d / d1);
            case TEXT('^2'):
            {
                r = d * d;
                dstack.push(r);
            }
            case TEXT('(-1)'):
            {
                r = d * (-1);
                dstack.push(r);
            }
            case TEXT('sqrt'):
            {
                r = sqrt(d);
                dstack.push(r);
            }
            case TEXT('1/x'):
            {
                r = 1. / d;
                dstack.push(r);
            }
                break;
            }
        }
    }
    if (1 == dstack.size())
    {
        _stprintf(buf, TEXT("%lf"), dstack.top());
        dstack.pop();
    }
    else
    {
        _stprintf(buf, TEXT("error"));
    }
    return buf;
}