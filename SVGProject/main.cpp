#include "stdafx.h"
#include"Shape.h"
#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>

#include <shellapi.h>

using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")

struct Paint {
    Drawer shape;
};

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

INT WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR cmdLine, INT iCmdShow)
{
    HWND                hWnd;
    MSG                 msg;
    WNDCLASS            wndClass;
    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR           gdiplusToken;

    //Entering command line
    int argc;
    LPWSTR* cmd = CommandLineToArgvW(cmdLine, &argc);

    wstring ws(cmd[0]);
    string file = string(ws.begin(), ws.end());
    size_t foundSVG = file.find(".svg");
    if (foundSVG == string::npos) file = "svg-18.svg";
    file = "SVGFolder/" + file;

    Drawer shape;
    shape.readData(file);

    Paint* pState = new Paint;
    pState->shape = shape;

    // Initialize GDI+.
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    wndClass.style = CS_HREDRAW | CS_VREDRAW;
    wndClass.lpfnWndProc = WndProc;
    wndClass.cbClsExtra = 0;
    wndClass.cbWndExtra = 0;
    wndClass.hInstance = hInstance;
    wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndClass.lpszMenuName = NULL;
    wndClass.lpszClassName = TEXT("GettingStarted");

    RegisterClass(&wndClass);

    hWnd = CreateWindowEx(
        0,
        TEXT("GettingStarted"),   // window class name
        TEXT("SVG Render"),         // window caption
        WS_OVERLAPPEDWINDOW,      // window style
        CW_USEDEFAULT,            // initial x position
        CW_USEDEFAULT,            // initial y position
        CW_USEDEFAULT,            // initial x size
        CW_USEDEFAULT,            // initial y size
        NULL,                     // parent window handle
        NULL,                     // window menu handle
        hInstance,                // program instance handle
        pState);                    // creation parameters

    ShowWindow(hWnd, iCmdShow);
    UpdateWindow(hWnd);

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    GdiplusShutdown(gdiplusToken);
    return msg.wParam;
}  // WinMain

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC          hdc;
    PAINTSTRUCT  ps;

    //Read file from command line
    LONG_PTR ptr;
    Paint* paint;
    if (message == WM_CREATE)
    {
        CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
        paint = reinterpret_cast<Paint*>(pCreate->lpCreateParams);
        SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)paint);
    }


    switch (message)
    {
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);

        ptr = GetWindowLongPtr(hWnd, GWLP_USERDATA);
        paint = reinterpret_cast<Paint*>(ptr);
        // Render here
        paint->shape.Draw(hdc);

        EndPaint(hWnd, &ps);
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
} // WndProc