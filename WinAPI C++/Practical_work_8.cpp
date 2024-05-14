// TEST01.cpp : Определяет точку входа для приложения.
//

#include "windows.h"
#include"resource.h"
#include <cstdlib>
#define MAIN_WINDOW "Mainwnd"
#define WINDOW_NAME "Main window"
#define MULTIPILER 0.7
#define N 400
#define M 250
#define INDENT 70

struct Colorpix {
    BYTE array[N][M] = { false };
    POINT pnt;
};

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

    HWND hWnd = CreateWindow(wc.lpszClassName, WINDOW_NAME, WS_OVERLAPPEDWINDOW,
        pxy.x,
        pxy.y,
        (LONG)(GetSystemMetrics(SM_CXSCREEN) * MULTIPILER),
        (LONG)(GetSystemMetrics(SM_CYSCREEN) * MULTIPILER),
        NULL, LoadMenuA(hInstance, MAKEINTRESOURCE(IDC_PRACTICALWORK8)), hInstance, NULL);

    Colorpix *pxls = new Colorpix;
    pxls->pnt.x = 0;
    pxls->pnt.y = 0;
    ZeroMemory(pxls->array, M * N);

    SetWindowLong(hWnd, GWLP_USERDATA, (LONG)pxls);

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

    delete pxls;

    return 0;
}



LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_SIZING:{

        RECT* rsRect = (RECT*) lParam;
        switch (wParam) {
            
        case WMSZ_BOTTOM: {
            
            rsRect->bottom = (LONG) max(rsRect->top + M * 1.2 + INDENT, rsRect->bottom);
            break;
        }
        case WMSZ_TOP: {

            rsRect->top = (LONG)min(rsRect->bottom - M * 1.2 + INDENT, rsRect->top);
          
            break;
        }
        case WMSZ_LEFT: {

            rsRect->left = (LONG)min(rsRect->right - N * 1.2, rsRect->left);

            break;
        }
        case WMSZ_RIGHT: {

            rsRect->right = (LONG)max(rsRect->left + N * 1.2, rsRect->right);

            break;
        }
        case WMSZ_BOTTOMLEFT: {

            rsRect->bottom = (LONG)max(rsRect->top + M * 1.2 + INDENT, rsRect->bottom);
            rsRect->left = (LONG)min(rsRect->right - N * 1.2, rsRect->left);
            break;
        }
        case WMSZ_BOTTOMRIGHT: {

            rsRect->bottom = (LONG)max(rsRect->top + M * 1.2 + INDENT, rsRect->bottom);
            rsRect->right = (LONG)max(rsRect->left + N * 1.2, rsRect->right);

            break;
        }
        case WMSZ_TOPLEFT: {

            rsRect->top = (LONG)min(rsRect->bottom - M * 1.2 + INDENT, rsRect->top);
            rsRect->left = (LONG)min(rsRect->right - N * 1.2, rsRect->left);

            break;
        }
        case WMSZ_TOPRIGHT: {

            rsRect->top = (LONG)min(rsRect->bottom - M * 1.2 + INDENT, rsRect->top);
            rsRect->right = (LONG)max(rsRect->left + N * 1.2, rsRect->right);

            break;
        }
        }
        return 0;
    }

    case WM_COMMAND: {

        switch (LOWORD(wParam)) {

        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        }

        return 0;
    }
    case WM_PAINT: {

        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        Colorpix* pxls = (Colorpix*)GetWindowLong(hWnd, GWLP_USERDATA);
        Rectangle(hdc, 0, 0, N, M);

        for(int i = 0; i < N; i++)
            for(int j = 0; j < M; j++)
                if(pxls->array[i][j])
                    SetPixelV(hdc, i, j, RGB(0,0,0));

        EndPaint(hWnd, &ps);
        return 0;
    }
    case WM_MOUSEMOVE: {

        
        POINT mcrdnt = { LOWORD(lParam), HIWORD(lParam) };
        RECT rprecrt = { 0, 0, N, M };
        Colorpix* pxls = (Colorpix*)GetWindowLong(hWnd, GWLP_USERDATA);

        if (PtInRect(&rprecrt, mcrdnt))
        {
            if (wParam == MK_LBUTTON)
            {
                HDC hdc = GetDC(hWnd);

                MoveToEx(hdc, pxls->pnt.x, pxls->pnt.y, NULL);
                LineTo(hdc, mcrdnt.x, mcrdnt.y);

                pxls->pnt.x = min(0, mcrdnt.x);
                pxls->pnt.x = max(N-1, mcrdnt.x);
                pxls->pnt.y = min(0, mcrdnt.y);
                pxls->pnt.y = max(M-1, mcrdnt.y);

                pxls->array[pxls->pnt.x][pxls->pnt.y] = true;

                for (int i = 1; i < abs(mcrdnt.x - pxls->pnt.x) ; i++)
                {
                    int y = int(pxls->pnt.y + (i)*((float)(mcrdnt.y - pxls->pnt.y) / (float)(mcrdnt.x - pxls->pnt.x)));
                    if (i < N && y < M)
                        pxls->array[i+ pxls->pnt.x][y] = true;
                }
                
                ReleaseDC(hWnd, hdc);
            }
            pxls->pnt = mcrdnt;
        }
            

        return 0;
    }

    case WM_DESTROY:

        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}
