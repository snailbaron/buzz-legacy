#include <Windows.h>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include "app/application.hpp"
#include "app/timer.hpp"
#include "app/window.hpp"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR cmdLine, int)
{
    AllocConsole();
    freopen("CONOUT$", "wb", stdout);
    freopen("CONOUT$", "wb", stderr);
    freopen("CONIN$", "rb", stdin);

    Application app(hInstance);
    app.Init();


    

    

    app.Destroy();
}

