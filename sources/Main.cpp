
#include "Defines.h"
#include "Main.h"
#include "WInformer.h"

const char* wdays[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };

class frame : public sciter::window
{
public:

    frame() : window(SW_MAIN|SW_ALPHA|SW_ENABLE_DEBUG){}

    void ProcessDateTime()
    {
        HWND        hWnd  = this->get_hwnd();
        std::time_t t_c   = std::chrono::system_clock::to_time_t( std::chrono::system_clock::now() );
        struct tm*  ptime = std::localtime(&t_c);
        /*
        struct tm
        {
            int tm_sec;   // seconds after the minute - [0, 60] including leap second
            int tm_min;   // minutes after the hour - [0, 59]
            int tm_hour;  // hours since midnight - [0, 23]
            int tm_mday;  // day of the month - [1, 31]
            int tm_mon;   // months since January - [0, 11]
            int tm_year;  // years since 1900
            int tm_wday;  // days since Sunday - [0, 6]
            int tm_yday;  // days since January 1 - [0, 365]
            int tm_isdst; // daylight savings time flag
        };*/

        std::string str_time;
        std::string str_day;
        std::string str_date;

        str_date = WUtils::string_format( "%02d.%02d.%04d",
                                    ptime->tm_mon + 1,
                                    ptime->tm_mday,
                                    ptime->tm_year + 1900);

        str_time = WUtils::string_format( "%02d:%02d:%02d",
                                    ptime->tm_hour,
                                    ptime->tm_min,
                                    ptime->tm_sec );

        str_day = wdays[ptime->tm_wday];
        
        sciter::dom::element root    = sciter::dom::element::root_element(hWnd);
        sciter::dom::element el_time = root.get_element_by_id("out-time");
        sciter::dom::element el_day  = root.get_element_by_id("out-day");
        sciter::dom::element el_date = root.get_element_by_id("out-date");

        std::wstring wstr_time( str_time.begin(), str_time.end() );
        std::wstring wstr_day ( str_day.begin(),  str_day.end() );
        std::wstring wstr_date( str_date.begin(), str_date.end() );

        el_time.set_text( wstr_time.c_str() );
        el_day .set_text( wstr_day.c_str() );
        el_date.set_text( wstr_date.c_str() );

    } // ProcessDateTime

    LRESULT on_message( HWINDOW hWnd, UINT msg, WPARAM wParam, LPARAM lParam, BOOL& pHandled )
    {
        switch(msg)
        {
            case WM_LBUTTONDOWN:
                ReleaseCapture();
                SendMessage( hWnd, WM_SYSCOMMAND, SC_MOVE|HTCAPTION, 0 );
            break;

            case WM_TIMER:
                if( wParam == 8001 )
                {
                    ProcessDateTime();
                }
            break;

        } // switch

        return 0;

    } // on_message

}; // class frame



int uimain(std::function<int()> run)
{
    frame*     pwin      = new frame();
    HWND      _hWnd      = pwin->get_hwnd();
    HINSTANCE _hInstance = ghInstance;

    pwin->load( WUtils::GetCurDirFullW( "/WInformer/Main.html" ).c_str() );

    SetWindowLong( _hWnd, GWL_STYLE, 0 );
    LONG lExStyle  = GetWindowLong( _hWnd, GWL_EXSTYLE );
         lExStyle &= ~( WS_EX_DLGMODALFRAME|WS_EX_CLIENTEDGE|WS_EX_STATICEDGE|WS_BORDER|WS_DLGFRAME|WS_SIZEBOX|WS_THICKFRAME );
    SetWindowLong( _hWnd, GWL_EXSTYLE, lExStyle );

    pwin->expand();

    SetWindowPos(_hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

    SetTimer( _hWnd, 8001, 1000, (TIMERPROC)NULL );
    
    return run();

} // uimain
