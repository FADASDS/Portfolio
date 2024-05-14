#include "windows.h"
#include"resource.h"

#define MULTIPILER 0.35
#define RADIX 10
#define ONE_DAY 864000000000
WCHAR resultStrEnumCalendarInfoProc[MAX_PATH / 2];
using namespace std;

BOOL CALLBACK EnumCalendarInfoProc(LPWSTR lpCalendarInfoString);

BOOL CALLBACK DlgProc(HWND hdlg, UINT message, WPARAM wParam, LPARAM lParam);

int APIENTRY WinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE, //hPrevInstance,
    _In_ LPSTR, //lpCmdLine,
    _In_ int       nCmdShow)
{
    
    RECT screen = { 0 };
    SystemParametersInfo(SPI_GETWORKAREA, NULL, &screen, NULL);

    POINT pxy = { 0 };
    pxy.x = (LONG)((GetSystemMetrics(SM_CXSCREEN) - (GetSystemMetrics(SM_CXSCREEN) * MULTIPILER)) / 2);
    pxy.y = (LONG)((screen.bottom - (GetSystemMetrics(SM_CYSCREEN) * MULTIPILER)) / 2);

    HWND DialogWnd = CreateDialogA(GetModuleHandle(NULL), MAKEINTRESOURCEA(IDD_DIALOG1), GetFocus(), (DLGPROC)DlgProc);
    
    if (!DialogWnd)
    {
        return -1;
    }
    SetWindowPos(DialogWnd, HWND_TOP, pxy.x, pxy.y, NULL, NULL, SWP_NOSIZE);
    ShowWindow(DialogWnd, SW_NORMAL);
    

    MSG msg;

    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

BOOL CALLBACK DlgProc(HWND hdlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {

    case WM_INITDIALOG: {

        SYSTEMTIME lt;
        GetLocalTime(&lt);

        WCHAR strDate[MAX_PATH / 2] = { 0 };
        WCHAR buff[MAX_PATH / 10] = { 0 };
        const WCHAR space[2] = { ' ' };


        lt.wDayOfWeek == 0 ?
            EnumCalendarInfo(EnumCalendarInfoProc,
                LOCALE_USER_DEFAULT,
                CAL_GREGORIAN,
                CAL_SDAYNAME1
            ) :
            EnumCalendarInfo(EnumCalendarInfoProc,
                LOCALE_USER_DEFAULT,
                CAL_GREGORIAN,
                CAL_SDAYNAME1 + lt.wDayOfWeek - 1);

        lstrcat(strDate, resultStrEnumCalendarInfoProc);
        _itow_s(lt.wDay, buff, RADIX);
        lstrcat(strDate, space);
        lstrcat(strDate, buff);
        lstrcat(strDate, space);

        EnumCalendarInfo(EnumCalendarInfoProc,
            LOCALE_NAME_USER_DEFAULT,
            CAL_GREGORIAN,
            CAL_RETURN_GENITIVE_NAMES | CAL_SMONTHNAME1 + lt.wMonth - 1
        );

        lstrcat(strDate, resultStrEnumCalendarInfoProc);
        lstrcat(strDate, space);
        _itow_s(lt.wYear, buff, RADIX);
        lstrcat(strDate, buff);

        SetDlgItemText(hdlg, IDC_EDIT2, (LPCWSTR)"0");
        SetDlgItemText(hdlg, CURRENT_TIME, strDate);

        return TRUE;

    }


    case WM_COMMAND: {
        switch (wParam) {

        case CALCULATETIME: {

            INT days;
            SYSTEMTIME st;
            FILETIME ft;
            ULARGE_INTEGER ui;
            INT64 maxDifference, minDifference;
            WCHAR strDate[MAX_PATH / 2] = { 0 };
            WCHAR buff[MAX_PATH / 10] = { 0 };
            const WCHAR space[2] = { ' ' };
            ULARGE_INTEGER ui_max;
            ui_max.QuadPart = MAXINT64;
            GetLocalTime(&st);
            SystemTimeToFileTime(&st, &ft);

            ui.LowPart = ft.dwLowDateTime;
            ui.HighPart = ft.dwHighDateTime;

            days = GetDlgItemInt(hdlg, IDC_EDIT2, NULL, TRUE);
            maxDifference = ui_max.QuadPart - ui.QuadPart;
            minDifference = -1 * ui.QuadPart;
            if (days == 0)
            {
                SetDlgItemInt(hdlg, IDC_EDIT2, 0, TRUE);
            }

            if (days * ONE_DAY > maxDifference)
            {
                SetDlgItemInt(hdlg, IDC_EDIT2, UINT(maxDifference/ONE_DAY), TRUE);
                days = GetDlgItemInt(hdlg, IDC_EDIT2, NULL, TRUE);

            }
            if (days * ONE_DAY < minDifference)
            {
                SetDlgItemInt(hdlg, IDC_EDIT2, UINT(minDifference / ONE_DAY), TRUE);
                days = GetDlgItemInt(hdlg, IDC_EDIT2, NULL, TRUE);

            }

            ui.QuadPart += days * ONE_DAY;
            ft.dwLowDateTime = ui.LowPart;
            ft.dwHighDateTime = ui.HighPart;
            FileTimeToSystemTime(&ft, &st);

            _itow_s(ui_max.QuadPart, buff, RADIX);
            MessageBox(hdlg, buff, NULL, MB_OK);
            _itow_s(ft.dwHighDateTime, buff, RADIX);
            MessageBox(hdlg, buff, NULL, MB_OK);

            st.wDayOfWeek == 0 ?
                EnumCalendarInfo(EnumCalendarInfoProc,
                    LOCALE_NAME_USER_DEFAULT,
                    CAL_GREGORIAN,
                    CAL_SDAYNAME1
                ) :
                EnumCalendarInfo(EnumCalendarInfoProc,
                    LOCALE_USER_DEFAULT,
                    CAL_GREGORIAN,
                    CAL_SDAYNAME1 + st.wDayOfWeek - 1);

            lstrcat(strDate, resultStrEnumCalendarInfoProc);
            lstrcat(strDate, space);
            _itow_s(st.wDay, buff, RADIX);
            lstrcat(strDate, buff);
            lstrcat(strDate, space);

            EnumCalendarInfo(EnumCalendarInfoProc, 
                LOCALE_USER_DEFAULT, 
                CAL_GREGORIAN, 
                CAL_RETURN_GENITIVE_NAMES|CAL_SMONTHNAME1 + st.wMonth - 1);

            lstrcat(strDate, resultStrEnumCalendarInfoProc);
            lstrcat(strDate, space);
            _itow_s(st.wYear, buff, RADIX);
            lstrcat(strDate, buff);

            SetDlgItemText(hdlg, CALCULATEDTIME, strDate);

            return TRUE;
        } 


        case IDCANCEL: {

            DestroyWindow(hdlg);
            return TRUE;
        }

        }
        return TRUE;
    }
    case WM_DESTROY: {

        PostQuitMessage(0); 
        break;
    }
    }
    return FALSE;
}

BOOL CALLBACK EnumCalendarInfoProc(LPWSTR lpCalendarInfoString)
{
    lstrcpy(resultStrEnumCalendarInfoProc, lpCalendarInfoString);
    return TRUE;
}