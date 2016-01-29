#include <Windows.h>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include "app/application.hpp"
#include "app/timer.hpp"
#include "app/window.hpp"
#include "gl_funcs.hpp"
#include "errors.hpp"
#include "app/shader.hpp"
#include "app/program.hpp"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR cmdLine, int)
{
    try {

        AllocConsole();
        freopen("CONOUT$", "wb", stdout);
        freopen("CONOUT$", "wb", stderr);
        freopen("CONIN$", "rb", stdin);

        g_app = Application(hInstance);
        g_app.Init();

        g_app.Start();

    
        g_app.Destroy();

    } catch (WindowsError werr) {
        std::cerr << "Windows error: " << werr.WindowsErrCode() << std::endl;
        std::cerr << "Message: " << werr.WindowsErrMessage() << std::endl;
    } catch (OpenGLError err) {
        std::cerr << "OpenGL error: " << err.OglErrName() << " (" << err.OglErrCode() << ")" << std::endl;
    } catch (Error err) {
        std::cerr << "Error: " << err.ErrCode() << std::endl;
    }

    getchar();
}

