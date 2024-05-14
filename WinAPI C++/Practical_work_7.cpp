// TEST01.cpp : Определяет точку входа для приложения.
//

#include "windows.h"
#include"resource.h"
#include <stdio.h>
#define MAIN_WINDOW "Mainwnd"
#define WINDOW_NAME "Main window"
#define MULTIPILER 0.7
#define BUTTON_INDENT 15
#define BUTTON_NUM 5000
#define BUTTON_HEIGHT 25
#define BUTTON_WIDTH 100
#define FIRST_BTN 0
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int APIENTRY WinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE, //hPrevInstance,
    _In_ LPSTR, //lpCmdLine,
    _In_ int       nCmdShow)
{

    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = MAIN_WINDOW;
    wc.hbrBackground = HBRUSH(COLOR_BTNFACE + 1);

    if (!RegisterClass(&wc))
    {
        return -1;
    }
    RECT screen;
    SystemParametersInfo(SPI_GETWORKAREA, NULL, &screen, NULL);

    POINT pxy;
    pxy.x = (LONG)((GetSystemMetrics(SM_CXSCREEN) - (GetSystemMetrics(SM_CXSCREEN) * MULTIPILER)) / 2);
    pxy.y = (LONG)((screen.bottom - (GetSystemMetrics(SM_CYSCREEN) * MULTIPILER)) / 2);

    HWND hWnd = CreateWindow(MAIN_WINDOW, WINDOW_NAME, WS_OVERLAPPEDWINDOW | WS_VSCROLL,
        pxy.x,
        pxy.y,
        (LONG)(GetSystemMetrics(SM_CXSCREEN) * MULTIPILER),
        (LONG)(GetSystemMetrics(SM_CYSCREEN) * MULTIPILER),
        NULL, NULL, hInstance, NULL);

    if (!hWnd)
    {
        return -1;
    }
    ShowWindow(hWnd, nCmdShow);


    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE: {

        char buff[20] = { 0 };
        int k = 1;
        for (int i = 0;i < BUTTON_NUM;i += 2)
        {
            
            wsprintf(buff, "Кнопка %d", k);
            CreateWindow("BUTTON", buff,
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                BUTTON_INDENT,
                BUTTON_INDENT * k + BUTTON_HEIGHT * (k-1),
                BUTTON_WIDTH,
                BUTTON_HEIGHT,
                hWnd,
                HMENU(i),
                GetModuleHandle(NULL), NULL);

            sprintf_s(buff, "Радио %d", k);

            CreateWindow("BUTTON", buff,
                WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON,
                2 * BUTTON_WIDTH + BUTTON_INDENT,
                BUTTON_INDENT * k + BUTTON_HEIGHT * (k - 1),
                BUTTON_WIDTH,
                BUTTON_HEIGHT,
                hWnd,
                HMENU(i + 1),
                GetModuleHandle(NULL), NULL);
            k++;
        }
        SendDlgItemMessage(hWnd, FIRST_BTN, BM_SETSTATE, BN_PUSHED, NULL);
        SendDlgItemMessage(hWnd, FIRST_BTN + 1, BM_SETCHECK, BST_CHECKED, NULL);
        SetWindowLong(hWnd, GWLP_USERDATA, FIRST_BTN);
        return 0;
    }


    case WM_SIZE: {
        RECT screen;
        SystemParametersInfo(SPI_GETWORKAREA, NULL, &screen, NULL);
        RECT rc;
        GetClientRect(hWnd, &rc);
        SCROLLINFO scroll = { 0 };
        scroll.cbSize = sizeof(SCROLLINFO);
        scroll.fMask = SIF_RANGE;
        scroll.nMin = 0;
        int n = (BUTTON_NUM / 2 - (screen.bottom - BUTTON_HEIGHT) / (BUTTON_INDENT + BUTTON_HEIGHT));
        scroll.nMax = BUTTON_HEIGHT * n + (BUTTON_INDENT * (n - 1));
        //scroll.nMax = (BUTTON_HEIGHT + BUTTON_INDENT) * (BUTTON_NUM/2) - rc.bottom ;
        SetScrollInfo(hWnd, SB_VERT, &scroll, TRUE);
        //InvalidateRect(hWnd, NULL, TRUE);

        return 0;
    }


    case WM_COMMAND: {

        int btn_num = GetWindowLong(hWnd, GWLP_USERDATA);
       
        int Id = LOWORD(wParam);
        if (Id % 2 != 0)
            {
                Id -= 1;
            }
            SendDlgItemMessage(hWnd, Id + 1, BM_SETCHECK, BST_CHECKED, NULL);
            SendDlgItemMessage(hWnd, Id, BM_SETSTATE, BN_PUSHED, NULL);
            SendDlgItemMessage(hWnd, btn_num, BM_SETSTATE, BST_UNCHECKED, NULL);
            SendDlgItemMessage(hWnd, btn_num + 1, BM_SETCHECK, BST_UNCHECKED, NULL);
            SetWindowLong(hWnd, GWLP_USERDATA, Id);
        return 0;
    }

    case WM_VSCROLL: {
        SCROLLINFO vscroll = { 0 };
        vscroll.cbSize = sizeof(SCROLLINFO);
        vscroll.fMask = SIF_RANGE | SIF_POS | SIF_TRACKPOS;
        GetScrollInfo(hWnd, SB_VERT, &vscroll);
        int nyPos = vscroll.nPos;
        switch (LOWORD(wParam)) {

        case SB_PAGEDOWN: //На страницу вниз
            nyPos += BUTTON_HEIGHT + BUTTON_INDENT;

            break;

        case SB_LINEDOWN: //На одну линию вниз
            nyPos += BUTTON_INDENT;

            break;

        case SB_PAGEUP: //На страницу вверх
            nyPos -= BUTTON_HEIGHT + BUTTON_INDENT;

            break;

        case SB_LINEUP: //На линию вверх
            nyPos -= BUTTON_INDENT;

            break;

        case SB_BOTTOM:
            nyPos = vscroll.nMax;
            break;

        case SB_TOP:
            nyPos = vscroll.nMin;
            break;

        case SB_THUMBTRACK:
            nyPos = HIWORD(wParam);
            break;

        default: break;
        }

        nyPos = max(0, nyPos);
        nyPos = min(vscroll.nMax, nyPos);

        // If the current position does not change, do not scroll.
        if (nyPos == vscroll.nPos)
            return 0;
        int yDelta = nyPos - vscroll.nPos;
        vscroll.nPos = nyPos;
        ScrollWindow(hWnd, 0, -yDelta, NULL, NULL);
        SetScrollInfo(hWnd, SB_VERT, &vscroll, TRUE);

        return 0;
    }
    case WM_KEYDOWN: {
        switch (wParam) {
        
        case VK_UP:
            PostMessage(hWnd, WM_VSCROLL, SB_LINEUP, NULL);
            break;

        case VK_DOWN:
            PostMessage(hWnd, WM_VSCROLL, SB_LINEDOWN, NULL);
            break;

        case VK_PRIOR:

            PostMessage(hWnd, WM_VSCROLL, SB_PAGEUP, NULL);

            break;

        case VK_NEXT:

            PostMessage(hWnd, WM_VSCROLL, SB_PAGEDOWN, NULL);

            break;

        case VK_HOME:

            PostMessage(hWnd, WM_VSCROLL, SB_TOP, NULL);

            break;

        case VK_END:

            PostMessage(hWnd, WM_VSCROLL, SB_BOTTOM, NULL);

            break;
        }
        return 0;
    }

    case WM_DESTROY:

        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}
