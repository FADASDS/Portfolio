#include "windows.h"
#include"resource.h"
#include <iostream>
#include <stdio.h>

#define MAIN_WINDOW "Main window"
#define MAX_LOADSTRING 10000
#define RECT_X 80
#define RECT_Y 26
#define MULTIPILER 0.7
#define N 20000

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void CreateLinearMatrix(int *BigMatrix);
void CreateSpiralMatrix(int* BigMatrix);

int APIENTRY WinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE, //hPrevInstance,
    _In_ LPSTR, //lpCmdLine,
    _In_ int nCmdShow)
{

    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = MAIN_WINDOW;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);


    if (!RegisterClass(&wc))
    {
        return -1;
    }
    RECT screen;
    SystemParametersInfo(SPI_GETWORKAREA, NULL, &screen, NULL);

    POINT pxy;
    pxy.x = (LONG)((GetSystemMetrics(SM_CXSCREEN) - (GetSystemMetrics(SM_CXSCREEN) * MULTIPILER)) / 2);
    pxy.y = (LONG)((screen.bottom - (GetSystemMetrics(SM_CYSCREEN) * MULTIPILER)) / 2);

    HWND hWnd = CreateWindow(wc.lpszClassName, "Main Wnd", WS_OVERLAPPEDWINDOW | WS_HSCROLL | WS_VSCROLL,
        pxy.x,
        pxy.y,
        (LONG)(GetSystemMetrics(SM_CXSCREEN) * MULTIPILER),
        (LONG)(GetSystemMetrics(SM_CYSCREEN) * MULTIPILER),
        NULL, LoadMenuA(hInstance, MAKEINTRESOURCE(IDC_BIGMATRIX)), hInstance, NULL);

    
    int* BigMatrix;
    int size = sizeof(int) * N * N;
    
    do
    {
        try {

            BigMatrix = (int*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY | HEAP_GENERATE_EXCEPTIONS, size);
        }
           catch(...)
           { }

    } while (BigMatrix == NULL);


    if (!hWnd)
    {
        return -1;
    }

    SetWindowLong(hWnd, GWLP_USERDATA, (LONG)BigMatrix);
    ShowWindow(hWnd, nCmdShow);
    EnableMenuItem(GetMenu(hWnd), IDM_LINEAR, MF_GRAYED);
    CreateLinearMatrix(BigMatrix);

    MSG msg;

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

    case WM_SIZE: {

        SCROLLINFO scrollinfo;
        RECT rectClient;
        
        GetClientRect(hWnd, &rectClient);

        int nX = int(rectClient.right / RECT_X) + 1;
        int nY = int(rectClient.bottom / RECT_Y) + 1;

        scrollinfo.cbSize = sizeof(scrollinfo);
        scrollinfo.fMask = SIF_RANGE | SIF_PAGE;
        scrollinfo.nMin = 0;
        scrollinfo.nMax = N * RECT_Y;
        scrollinfo.nPage = nY * RECT_Y;
        SetScrollInfo(hWnd, SB_VERT, &scrollinfo, TRUE);

        scrollinfo.cbSize = sizeof(scrollinfo);
        scrollinfo.fMask = SIF_RANGE | SIF_PAGE;
        scrollinfo.nMin = 0;
        scrollinfo.nMax = N * RECT_X;
        scrollinfo.nPage = nX * RECT_X;
        SetScrollInfo(hWnd, SB_HORZ, &scrollinfo, TRUE);

        InvalidateRect(hWnd, NULL, TRUE);
       
    }
    return 0;

    case WM_VSCROLL:
    {
        SCROLLINFO scrollinfo;
        scrollinfo.cbSize = sizeof(scrollinfo);
        scrollinfo.fMask = SIF_ALL;
        GetScrollInfo(hWnd, SB_VERT, &scrollinfo);

        int yPos = scrollinfo.nPos;
        switch (LOWORD(wParam))
        {
        case SB_TOP: 
            scrollinfo.nPos = scrollinfo.nMin; 
            break;

        case SB_BOTTOM: 
            scrollinfo.nPos = scrollinfo.nMax; 
            break;

        case SB_LINEUP: 
            scrollinfo.nPos -= RECT_Y; 
            break;

        case SB_LINEDOWN: 
            scrollinfo.nPos += RECT_Y; 
            break;

        case SB_PAGEUP: 
            scrollinfo.nPos -= scrollinfo.nPage; 
            break;

        case SB_PAGEDOWN: 
            scrollinfo.nPos += scrollinfo.nPage; 
            break;

        case SB_THUMBTRACK: 
            scrollinfo.nPos = scrollinfo.nTrackPos; 
            break;

        default: break;
        }

        scrollinfo.fMask = SIF_POS;
        SetScrollInfo(hWnd, SB_VERT, &scrollinfo, TRUE);
        GetScrollInfo(hWnd, SB_VERT, &scrollinfo);


        if (scrollinfo.nPos != yPos)
        {
            ScrollWindow(hWnd, 0, yPos - scrollinfo.nPos, NULL, NULL);
            InvalidateRect(hWnd, NULL, TRUE);
        }
      
    }
    return 0;

    case WM_HSCROLL:
    {
        SCROLLINFO scrollinfo;
        scrollinfo.cbSize = sizeof(scrollinfo);
        scrollinfo.fMask = SIF_ALL;

        GetScrollInfo(hWnd, SB_HORZ, &scrollinfo);
        int xPos = scrollinfo.nPos;
        switch (LOWORD(wParam))
        {

        case SB_LINELEFT:
            scrollinfo.nPos -= RECT_X;
            break;

        case SB_LINERIGHT:
            scrollinfo.nPos += RECT_X;
            break;

        case SB_PAGELEFT:
            scrollinfo.nPos -= scrollinfo.nPage;
            break;

        case SB_PAGERIGHT:
            scrollinfo.nPos += scrollinfo.nPage;
            break;

        case SB_THUMBTRACK:
            scrollinfo.nPos = scrollinfo.nTrackPos;
            break;

        default:
            break;
        }

        scrollinfo.fMask = SIF_POS;
        SetScrollInfo(hWnd, SB_HORZ, &scrollinfo, TRUE);
        GetScrollInfo(hWnd, SB_HORZ, &scrollinfo);


        if (scrollinfo.nPos != xPos)
        {
            ScrollWindow(hWnd, xPos - scrollinfo.nPos, 0, NULL, NULL);
            InvalidateRect(hWnd, NULL, TRUE);
        }

        return 0;
    }
    return 0;

    case WM_PAINT:
    {
        int* BigMatrix = (int*)GetWindowLong(hWnd, GWLP_USERDATA);

        SCROLLINFO scrollinfo;
        scrollinfo.cbSize = sizeof(scrollinfo);
        scrollinfo.fMask = SIF_POS;

        GetScrollInfo(hWnd, SB_VERT, &scrollinfo);
        int yPos = scrollinfo.nPos/RECT_Y;

        GetScrollInfo(hWnd, SB_HORZ, &scrollinfo);
        int xPos = scrollinfo.nPos/ RECT_X;

        RECT rectClient, rect;
        PAINTSTRUCT ps;

        HANDLE consoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
        char buff[MAX_PATH / 10] = { 0 };

       

        HDC hdc = BeginPaint(hWnd, &ps);

        GetClientRect(hWnd, &rectClient);

        HMENU hMenu = GetMenu(hWnd);
        
        int nY = int(rectClient.bottom / RECT_Y) + 2;
        int nX = int(rectClient.right / RECT_X) + 1;

        for (int i = 0; i < nY; i++) {

            for (int j = 0; j < nX; j++) {

                int virtualRow = i + yPos;
                int virtualColumn = j + xPos;

                snprintf(buff, sizeof(buff), "%d", BigMatrix[virtualColumn + N * virtualRow]);

                SetRect(&rect, RECT_X* j,
                    RECT_Y * i,
                    RECT_X * j + RECT_X,
                    RECT_Y * i + RECT_Y);

                DrawText(hdc, (LPCSTR)buff, -1, &rect, DT_LEFT);

            }
        }
        EndPaint(hWnd, &ps);
        return 0;
    }
    return 0;

    case WM_COMMAND:
    {
        switch (LOWORD(wParam)) {
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        case IDM_LINEAR:
        {
            int* BigMatrix = (int*)GetWindowLong(hWnd, GWLP_USERDATA);
            EnableMenuItem(GetMenu(hWnd), IDM_LINEAR, MF_GRAYED);
            EnableMenuItem(GetMenu(hWnd), IDM_SPIRAL, MF_ENABLED);
            CreateLinearMatrix(BigMatrix);
            InvalidateRect(hWnd, NULL, TRUE);
            break;
        }
        case IDM_SPIRAL:
        {
            int* BigMatrix = (int*)GetWindowLong(hWnd, GWLP_USERDATA);
            EnableMenuItem(GetMenu(hWnd), IDM_SPIRAL, MF_GRAYED);
            EnableMenuItem(GetMenu(hWnd), IDM_LINEAR, MF_ENABLED);
            CreateSpiralMatrix(BigMatrix);
            InvalidateRect(hWnd, NULL, TRUE);
            break;
        }
        }
        return 0;
    }
    return 0;

    case WM_KEYDOWN:
        switch (wParam) {
        case VK_LEFT:
            PostMessage(hWnd, WM_HSCROLL, SB_LINELEFT, NULL);
            break;

        case VK_RIGHT:
            PostMessage(hWnd, WM_HSCROLL, SB_LINERIGHT, NULL);
            break;

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

    case WM_DESTROY:
    {
        int * BigMatrix = (int*)GetWindowLong(hWnd, GWLP_USERDATA);
        HeapFree(GetProcessHeap(), NULL, BigMatrix);
        PostQuitMessage(0);
    }
    return 0;
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}

    void CreateLinearMatrix(int *BigMatrix) {

        for (int i = 0; i < N; i++) {
            
            for (int j = 0; j < N; j++) {

                BigMatrix[j + N * i] = (j+1)+N*i;

            }
        }
    }

    void CreateSpiralMatrix(int* BigMatrix) {

        int bottom = N-1, right = N-1,top = 0, left = 0, value = 1;

        while (top <= bottom && left <= right) {

            for (int col = left; col < right; col++) {

                BigMatrix[col + top * N] = value++;

            }

            for (int row = top; row <= bottom; row++) {

                BigMatrix[right + row * N] = value++;

            }

            if (top < bottom) {

                for (int col = right - 1; col >= left; col--) 

                    BigMatrix[col + bottom * N] = value++;

            }

            if (left < right) {

                for (int row = bottom - 1; row > top; --row)

                    BigMatrix[row * N + left] = value++;

            }

            
            ++top;
            --bottom;
            ++left;
            --right;
        }
        
    }