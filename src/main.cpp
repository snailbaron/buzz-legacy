#include <iostream>
#include <Windows.h>
#include <gl/GL.h>
#include "glext.h"
#include "wglext.h"
#include "error.hpp"
#include "dummy_ogl_window.hpp"
#include "gl_funcs_def.hpp"
#include "main_window.hpp"

void ReportError(const char *msg)
{
    MessageBox(NULL, msg, "Error", MB_OK | MB_ICONERROR);
}

static const CHAR WND_CLASS_NAME[] = "MainWindowClass";
static const CHAR WND_NAME[] = "MainWindow";

LRESULT CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    switch (msg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProc(hwnd, msg, wparam, lparam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
    try {


    // Get OpenGL and platform-specific function pointers using
    // a dummy OpenGL context.
    DummyOglWindow *dummyWnd = new DummyOglWindow(hInstance);
    LoadGlFuncs();
    delete dummyWnd;


    // Create proper window
    MainWindow *wnd = new MainWindow(hInstance);

    // Enter main loop
    bool done = false;
    while (!done) {
        MSG msg;
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                done = true;
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        // Do stuff
    }

    delete wnd;



    } catch (Error err) {
        switch (err.ErrCode()) {
            case ERR_CREATE_WINDOW_CLASS:
                ReportError("Failed to create window class");
        }
    }

    return 0;
}