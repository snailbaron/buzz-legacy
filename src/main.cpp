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

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
    try {

    // Get OpenGL and platform-specific function pointers using
    // a dummy OpenGL context.
    DummyOglWindow dummyWnd(hInstance);
    dummyWnd.Init();
    LoadGlFuncs();
    dummyWnd.Destroy();

    // Create proper window
    MainWindow wnd(hInstance);
    wnd.Init();

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



    } catch (Error err) {
        switch (err.ErrCode()) {
            case ERR_CREATE_WINDOW_CLASS:
                ReportError("Failed to create window class");
        }
    }

    return 0;
}