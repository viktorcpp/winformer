
WInformer::WInformer()
{
    //
}

WInformer::WInformer( HINSTANCE _hInstance )
{
    hInstance = _hInstance;
}

void WInformer::Setup() throw(std::exception)
{

    OleInitialize(0); // for drag-n-drop
    ::SciterSetOption( NULL, SCITER_SET_UX_THEMING, TRUE );

    WNDCLASSEX wcex = {};

    wcex.cbSize         = sizeof(WNDCLASSEX);
    wcex.style          = CS_CLASSDC;
    wcex.lpfnWndProc    = WInformer::WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = NULL;//LoadIcon( hInstance, MAKEINTRESOURCE( 0 ) );
    wcex.hIconSm        = NULL;//LoadIcon( wcex.hInstance, MAKEINTRESOURCE( 0 ) );
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);;
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = "CLASSNAME";

    RegisterClassEx(&wcex);

    //     CreateWindow(lpClassName, lpWindowName, dwStyle, x, y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam)
    hWnd = CreateWindow(
        "CLASSNAME",
        "APPNAME",
        1 ? WS_VISIBLE|WS_POPUP : WS_VISIBLE|WS_OVERLAPPED,
        0,
        0,
        200,
        100,
        GetDesktopWindow(),
        NULL,
        hInstance,
        (LPVOID) this);
        
    if( !hWnd )
    {
        throw std::exception( "CreateWindow FAILED" );
    }

    sciter::attach_dom_event_handler( hWnd , &sciter::event_handler );

    ShowWindow( hWnd, SW_SHOWDEFAULT );
    UpdateWindow( hWnd );
}

void WInformer::Run() throw(std::exception)
{
    MSG _msg;

    ZeroMemory( &_msg, sizeof(_msg) );

    while( _msg.message != WM_QUIT )
    {
        if( GetMessage( &_msg, NULL, 0, 0 ) )
        {
            TranslateMessage(&_msg);
            DispatchMessage(&_msg);
        }

    } // while
}

WInformer::~WInformer(){}

LRESULT CALLBACK WInformer::WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    switch( message )
    {
    case WM_CREATE:
        SetForegroundWindow(hWnd);
        break;

    case WM_ACTIVATE:
        SetForegroundWindow(hWnd);
        break;

    case WM_DESTROY:
    case WM_QUIT:
        PostQuitMessage(0);
        break;

    default:
        break;
    }

    return DefWindowProc( hWnd, message, wParam, lParam );

} // WndProc
