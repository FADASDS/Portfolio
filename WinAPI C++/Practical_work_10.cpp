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

BYTE** resize_func(int n, int m, int old_n, int old_m, BYTE**old_arr) {

    BYTE** newarr = new BYTE * [n];

    for (int i = 0;i < n;i++)
        newarr[i] = new BYTE[m];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            newarr[i][j] = 0;
    //ZeroMemory(newarr,n*m*sizeof(newarr[0][0]));

    if (n <= old_n && m <= old_m)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
            {
                 newarr[i][j] = old_arr[i][j];
               // memcpy(newarr[i], old_arr[i], m);
            }

    if (n >= old_n && m >= old_m)
        for (int i = 0; i < old_n; i++)
            for (int j = 0; j < old_m; j++)
            {
                 newarr[i][j] = old_arr[i][j];
               // memcpy(newarr[i], old_arr[i], m);
            }

    if (n >= old_n && m <= old_m)
        for (int i = 0; i < old_n; i++)
            for (int j = 0; j < m; j++)
            {
                 newarr[i][j] = old_arr[i][j];
                //memcpy(newarr[i], old_arr[i], m);
            }

    if (n <= old_n && m >= old_m)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < old_m; j++)
            {
                 newarr[i][j] = old_arr[i][j];
                //memcpy(newarr[i], old_arr[i], m);
            }

               

    for (int i = 0;i < old_n;i++)
        delete[] old_arr[i];
    delete[] old_arr;

    return newarr;
}
struct Colorpix {
    int n = N;
    int m = M;
    BYTE **arr = new BYTE*[N];
    POINT pnt = {0};
    int r = 0;
    int g = 0;
    int b = 0;
};

BOOL CALLBACK DlgProc(HWND hdlg, UINT message, WPARAM wParam, LPARAM lParam);
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
        NULL, LoadMenuA(hInstance, MAKEINTRESOURCE(IDC_PRACTICALWORK10)), hInstance, NULL);

    Colorpix pxls;
    pxls.pnt.x = 0;
    pxls.pnt.y = 0;
    
    for (int i = 0;i < N;i++)
        pxls.arr[i] = new BYTE[M];
   
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            pxls.arr[i][j] = 0;
    SetWindowLong(hWnd, GWLP_USERDATA, (LONG)&pxls);

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
    for (int i = 0;i < pxls.n;i++)
        delete[] pxls.arr[i];
    delete[] pxls.arr;
    return 0;
}



LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_SIZING: {
        Colorpix* pxls = (Colorpix*)GetWindowLong(hWnd, GWLP_USERDATA);
        RECT* rsRect = (RECT*)lParam;
        switch (wParam) {

        case WMSZ_BOTTOM: {

            rsRect->bottom = (LONG)max(rsRect->top + (pxls->m) * 1.2 + INDENT, rsRect->bottom);
            break;
        }
        case WMSZ_TOP: {

            rsRect->top = (LONG)min(rsRect->bottom - (pxls->m) * 1.2 + INDENT, rsRect->top);

            break;
        }
        case WMSZ_LEFT: {

            rsRect->left = (LONG)min(rsRect->right - (pxls->n) * 1.2, rsRect->left);

            break;
        }
        case WMSZ_RIGHT: {

            rsRect->right = (LONG)max(rsRect->left + (pxls->n) * 1.2, rsRect->right);

            break;
        }
        case WMSZ_BOTTOMLEFT: {

            rsRect->bottom = (LONG)max(rsRect->top + (pxls->m) * 1.2 + INDENT, rsRect->bottom);
            rsRect->left = (LONG)min(rsRect->right - (pxls->n) * 1.2, rsRect->left);
            break;
        }
        case WMSZ_BOTTOMRIGHT: {

            rsRect->bottom = (LONG)max(rsRect->top + (pxls->m) * 1.2 + INDENT, rsRect->bottom);
            rsRect->right = (LONG)max(rsRect->left + (pxls->n) * 1.2, rsRect->right);

            break;
        }
        case WMSZ_TOPLEFT: {

            rsRect->top = (LONG)min(rsRect->bottom - (pxls->m) * 1.2 + INDENT, rsRect->top);
            rsRect->left = (LONG)min(rsRect->right - (pxls->n) * 1.2, rsRect->left);

            break;
        }
        case WMSZ_TOPRIGHT: {

            rsRect->top = (LONG)min(rsRect->bottom - (pxls->m) * 1.2 + INDENT, rsRect->top);
            rsRect->right = (LONG)max(rsRect->left + (pxls->n) * 1.2, rsRect->right);

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

        case IDM_OPTIONS:

            DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG1), hWnd, (DLGPROC)DlgProc);
           
            break;
        }

        return 0;
    }
    case WM_PAINT: {

        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        Colorpix* pxls = (Colorpix*)GetWindowLong(hWnd, GWLP_USERDATA);
        Rectangle(hdc, 0, 0, pxls->n, pxls->m);

        for (int i = 0; i < pxls->n; i++)
            for (int j = 0; j < pxls->m; j++)
                if (pxls->arr[i][j])
                    SetPixelV(hdc, i, j, RGB(pxls->r, pxls->g, pxls->b));
        ReleaseDC(hWnd, hdc);
        EndPaint(hWnd, &ps);
        return 0;
    }
    case WM_MOUSEMOVE: {

        Colorpix* pxls = (Colorpix*)GetWindowLong(hWnd, GWLP_USERDATA);
        POINT mcrdnt = { LOWORD(lParam), HIWORD(lParam) };
        RECT rprecrt = { 0, 0, pxls->n, pxls->m };
        

        if (PtInRect(&rprecrt, mcrdnt))
        {
            if (wParam == MK_LBUTTON)
            {
                HDC hdc = GetDC(hWnd);
                HPEN hPen = CreatePen(PS_SOLID, 1, RGB(pxls->r, pxls->g, pxls->b));
                SelectObject(hdc, hPen);
                MoveToEx(hdc, pxls->pnt.x, pxls->pnt.y, NULL);
                if (mcrdnt.x == pxls->n-1 || mcrdnt.y == pxls->m-1)
                MoveToEx(hdc, mcrdnt.x, mcrdnt.y, NULL);
                LineTo(hdc, mcrdnt.x, mcrdnt.y);

                pxls->arr[pxls->pnt.x][pxls->pnt.y] = true;

                for (int i = 1; i < abs(mcrdnt.x - pxls->pnt.x); i++)
                {
                    int y = int(pxls->pnt.y + (i) * ((float)(mcrdnt.y - pxls->pnt.y) / (float)(mcrdnt.x - pxls->pnt.x)));
                    if (i + pxls->pnt.x < pxls->n && y < pxls->m)
                        pxls->arr[i + pxls->pnt.x][y] = true;
                }
                DeleteObject(hPen);
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
BOOL CALLBACK DlgProc(HWND hdlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {

        case WM_INITDIALOG: {

            SendMessage(GetDlgItem(hdlg, IDC_EDIT1), EM_LIMITTEXT, (WPARAM)4, 0);
            SendMessage(GetDlgItem(hdlg, IDC_EDIT2), EM_LIMITTEXT, (WPARAM)4, 0);
            return TRUE;

        }
     
        case WM_COMMAND: {
            switch (wParam) {

                case IDOK: {

                    

                    Colorpix* pxls = (Colorpix*)GetWindowLong(GetParent(hdlg), GWLP_USERDATA);

                    char buffed1[10] = {0};
                    char buffed2[10] = { 0 };

                    int old_n = pxls->n;
                    int old_m = pxls->m;
                    

                    GetWindowText(GetDlgItem(hdlg, IDC_EDIT1), buffed1, sizeof(buffed1));
                    GetWindowText(GetDlgItem(hdlg, IDC_EDIT2), buffed2, sizeof(buffed2));
                    //SendMessage(GetDlgItem(hdlg, IDC_EDIT1), EM_GETLINE, 0, (LPARAM)(LPSTR)buffed1);
                    //SendMessage(GetDlgItem(hdlg, IDC_EDIT2), EM_GETLINE, 0, (LPARAM)(LPSTR)buffed2);
                   
                    if (buffed1[0] == '\0' && buffed2[0] == '\0')
                    {
                        EndDialog(hdlg, IDCANCEL);
                    }
                        
                    else
                    {
                        RECT screen;
                        SystemParametersInfo(SPI_GETWORKAREA, NULL, &screen, NULL);

                        

                        if (buffed1[0] != '0' && buffed1[0] != '\0' && (atoi(buffed1)*1.2 < screen.right))
                        {
                            RECT rwindow;
                            GetWindowRect(GetParent(hdlg), &rwindow);

                            if (atoi(buffed1) > rwindow.right*0.8)
                            {
                                POINT pxy;
                                pxy.x = (LONG)((GetSystemMetrics(SM_CXSCREEN) - (int(atoi(buffed1) * 1.2))) / 2);
                                pxy.y = (LONG)((screen.bottom - rwindow.bottom) / 2);
                                SetWindowPos(GetParent(hdlg), NULL, pxy.x, pxy.y, int(atoi(buffed1)*1.2), rwindow.bottom, NULL);
                            }
                            pxls->n = atoi(buffed1);

                        }
                        else
                            if(buffed1[0] != '\0')
                            MessageBox(hdlg,"Неверно введено значение ширины!", NULL, MB_OK);

                        if (buffed2[0] != '0' && buffed2[0] != '\0' && (atoi(buffed2) * 1.2 < screen.bottom))
                        {
                            RECT rwindow;
                            GetWindowRect(GetParent(hdlg), &rwindow);

                            if (atoi(buffed2) > rwindow.bottom*0.8)
                            {
                                POINT pxy;
                                pxy.x = (LONG)((GetSystemMetrics(SM_CXSCREEN) - rwindow.right) / 2);
                                pxy.y = (LONG)((screen.bottom - int(atoi(buffed2) * 1.2)) / 2);
                                SetWindowPos(GetParent(hdlg), NULL, pxy.x, pxy.y, rwindow.right, int(atoi(buffed2) * 1.2), NULL);
                            }
                            pxls->m = atoi(buffed2);
                        }
                        else
                            if (buffed2[0] != '\0')
                            MessageBox(hdlg, "Неверно введено значение высоты!", NULL, MB_OK);
                       //BYTE** new_arr = resize_func(pxls->n, pxls->m, old_n, old_m, pxls->arr);
                       // pxls->arr = new_arr;
                        pxls->arr = resize_func(pxls->n, pxls->m, old_n, old_m, pxls->arr);
                    }
                        
                    InvalidateRect(GetParent(hdlg), NULL, TRUE);
                    EndDialog(hdlg, 0);
                    return TRUE;

                }
                case IDCANCEL: {

                    EndDialog(hdlg, 0);

                    return TRUE;
                }
                case IDC_BUTTON1: {

                    Colorpix* pxls = (Colorpix*)GetWindowLong(GetParent(hdlg), GWLP_USERDATA);
                    CHOOSECOLOR cc;
                    COLORREF cust_colors[1] = { 0 };
                    cc.Flags = CC_RGBINIT | CC_FULLOPEN;
                    cc.hInstance = NULL;
                    cc.hwndOwner = hdlg;
                    cc.lCustData = 0L;
                    cc.lpCustColors = cust_colors; //массив цветов
                    cc.lpfnHook = NULL;
                    cc.lpTemplateName = (LPSTR)NULL;
                    cc.lStructSize = sizeof(CHOOSECOLOR);  
                    cc.rgbResult = RGB(0, 0, 0); //цвет, заданный для диалога по умолчанию
                    if (ChooseColor(&cc))
                    {
                        pxls->r = GetRValue(cc.rgbResult);
                        pxls->g = GetGValue(cc.rgbResult);
                        pxls->b = GetBValue(cc.rgbResult);
                    }
                    //if (ChooseColor(&ch_color))
                    
                  
                }
                
            }
            return TRUE;
        }
    }
    return FALSE;
}
