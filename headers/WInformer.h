#pragma once

class WInformer
{
public:

    
    void Setup() throw(std::exception);
    void Run()   throw(std::exception);
    const HWND GetHWND(){ return this->hWnd; }

    static LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );

    WInformer();
    WInformer( HINSTANCE hInstance );

    virtual ~WInformer();

private:

    HINSTANCE  hInstance = nullptr;
    HWND       hWnd      = nullptr;

}; // WInformer
