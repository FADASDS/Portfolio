// TEST01.cpp : Определяет точку входа для приложения.
//

#include "windows.h"
#include"resource.h"
#define MAIN_WINDOW "Mainwnd"
#define WINDOW_NAME "Main window"
#define MULTIPILER 0.7



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
    wc.style = CS_HREDRAW | CS_VREDRAW;

    char num[20];
    LoadString(GetModuleHandle(NULL), IDS_STRING104, num, sizeof(num));// Загрузка строки из таблицы строк для заголовка главгого окна

    if (!RegisterClass(&wc))
    {
        return -1;
    }
    RECT screen;
    SystemParametersInfo(SPI_GETWORKAREA, NULL, &screen, NULL);

    POINT pxy;
    pxy.x = (LONG)((GetSystemMetrics(SM_CXSCREEN) - (GetSystemMetrics(SM_CXSCREEN) * MULTIPILER)) / 2);
    pxy.y = (LONG)((screen.bottom - (GetSystemMetrics(SM_CYSCREEN) * MULTIPILER)) / 2);

    HWND hWnd = CreateWindow(wc.lpszClassName, num, WS_OVERLAPPEDWINDOW,
        pxy.x,
        pxy.y,
        (LONG)(GetSystemMetrics(SM_CXSCREEN) * MULTIPILER),
        (LONG)(GetSystemMetrics(SM_CYSCREEN) * MULTIPILER),
        NULL, LoadMenuA(hInstance, MAKEINTRESOURCE(IDR_MENU1)), hInstance, NULL); // здесь устанавливается загруженная строка

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

HMENU createpopupwndfunc()//функция для создания меню
{
    HMENU hMenu = CreatePopupMenu();
    if (!hMenu)
        return NULL;
    char num[20];

    for (int i = IDS_STRING104; i <= IDS_STRING111; i++)
    {
        LoadString(GetModuleHandle(NULL), i, num, sizeof(num));
        if(strlen(num)!=0)
        AppendMenu(hMenu, MF_STRING, i, num);
    } //загрузка в меню пунктов из таблицы строк

    AppendMenu(hMenu, MF_SEPARATOR, NULL, NULL);//вставка разделителя в меню

    LoadString(GetModuleHandle(NULL), IDS_STRING108, num, sizeof(num));
    AppendMenu(hMenu, MF_STRING| MF_GRAYED, IDS_STRING108, num);// вставка строк, отвечающих за битмапы, их две

    LoadString(GetModuleHandle(NULL), IDS_STRING110, num, sizeof(num));
    AppendMenu(hMenu, MF_STRING, IDS_STRING110, num);

    return hMenu;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE: {
        HBITMAP hBMP = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP1));
        HBRUSH  hBrh = CreatePatternBrush(hBMP); // создаётся битмап из ресурсов, который будет фоном
        SetClassLong(hWnd, GCL_HBRBACKGROUND, (LONG)hBrh);

        HMENU hMenu = createpopupwndfunc();

        if (!hMenu)
            return -1;

        SetWindowLong(hWnd, GWLP_USERDATA, (LONG)hMenu);
        DeleteObject(hBMP);
        return 0;
    }

    case WM_COMMAND: {

        switch (LOWORD(wParam)) {

        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;


        case IDS_STRING108: {
            HMENU hMenu = (HMENU)GetWindowLong(hWnd, GWLP_USERDATA);
            HBITMAP hBMP = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP1));
            HBRUSH  hBrh = CreatePatternBrush(hBMP);

            if (!hBrh)
                return -1;

            HBRUSH holdBrh = (HBRUSH) GetClassLong(hWnd, GCL_HBRBACKGROUND);//получаем старую кисть фона (чтобы удалить еёи поставить новую)

            SetClassLong(hWnd, GCL_HBRBACKGROUND, (LONG)hBrh);

            InvalidateRect(hWnd, NULL, TRUE);

            DeleteObject(holdBrh);
            DeleteObject(hBMP);
            EnableMenuItem(hMenu, IDS_STRING108, MF_GRAYED);
            EnableMenuItem(hMenu, IDS_STRING110, MF_ENABLED);
            break;
        } //включение битмапа, как фон, в меню выбранный пункт будет некликабельным

        case IDS_STRING110: {
            HMENU hMenu = (HMENU)GetWindowLong(hWnd, GWLP_USERDATA);
            HBITMAP hBMP = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP2));
            HBRUSH  hBrh = CreatePatternBrush(hBMP);

            if (!hBrh)
                return -1;

            HBRUSH holdBrh = (HBRUSH) GetClassLong(hWnd, GCL_HBRBACKGROUND);
            
            SetClassLong(hWnd, GCL_HBRBACKGROUND, (LONG)hBrh);
            
            InvalidateRect(hWnd, NULL, TRUE);

            DeleteObject(holdBrh);
            DeleteObject(hBMP);
            EnableMenuItem(hMenu, IDS_STRING110, MF_GRAYED);
            EnableMenuItem(hMenu, IDS_STRING108, MF_ENABLED);
            break;
        }
        default: {
            char num[20];
            HMENU hMenu = (HMENU)GetWindowLong(hWnd, GWLP_USERDATA);
            GetMenuString(hMenu, LOWORD(wParam), num, sizeof(num), MF_BYCOMMAND);
            SetWindowText(hWnd, num);
            break; // здесь меняются заголовки окна
        }
        }
       
        return 0;
    }
    
    case WM_RBUTTONDOWN: {
        POINT pntcursor;
        GetCursorPos(&pntcursor);
        HMENU hMenu =  (HMENU)GetWindowLong(hWnd, GWLP_USERDATA);
        TrackPopupMenu(hMenu, TPM_CENTERALIGN , pntcursor.x, pntcursor.y, 0, hWnd, NULL);
        return 0;// здесь вызывается меню
    }
        
    case WM_DESTROY:
       
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}
