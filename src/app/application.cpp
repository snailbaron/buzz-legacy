#include "application.hpp"
#include <Windows.h>
#include <cstdio>

void Application::Start()
{
    AllocConsole();
    freopen("CONOUT$", "wb", stdout);
    freopen("CONOUT$", "wb", stderr);
    freopen("CONIN$", "rb", stdin);

}