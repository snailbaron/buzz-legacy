#ifndef _APPLICATION_HPP_
#define _APPLICATION_HPP_

#include <Windows.h>
#include "window.hpp"
#include <memory>
#include "../game/game.hpp"
#include "../view/human_game_view.hpp"

class Application
{
public:
    Application(HINSTANCE hInstance);
    ~Application();

    // Initialize OpenGL graphics
    void InitializeGfx();

    // Load OpenGL extension functions
    void LoadOpenGLFunctions();

    void Init();
    void Start();

    void Destroy();

private:
    // Platform-specific application info
    HINSTANCE m_hInstance;
    Window m_wnd;
    HDC m_oglDc;
    HGLRC m_hglrc;

    Game m_game;
    std::shared_ptr<HumanGameView> m_view;
};

#endif
