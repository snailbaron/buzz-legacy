#include <Windows.h>

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    // Some OpenGL initialization?

    // Application initialization
    //if (!g_app->InitInstance()) return false;

    // Main loop
    MSG msg;
    while (msg.message != WM_QUIT) {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        } else {
            // TODO: Render
        }
    }
    
        


    // Shutdown

    // Memory leak check

    // Exit code



    return 0;
}