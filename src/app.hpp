#ifndef _APP_HPP_
#define _APP_HPP_

#include <Windows.h>

class App
{
public:
    bool InitInstance(HINSTANCE hInstance, LPSTR cmdLine);

    //Game * CreateGameAndView();

private:
    HMODULE m_langDll;
    HINSTANCE m_hInstance;
    bool m_isRunning;


    // TODO: m_gameOptions;
    

    



};

#endif
