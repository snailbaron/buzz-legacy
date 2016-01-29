#ifndef _APPLICATION_HPP_
#define _APPLICATION_HPP_

#include <Windows.h>
#include "ogl_window.hpp"
#include <memory>
#include "../game/game.hpp"
#include "../view/human_game_view.hpp"
#include "program.hpp"

class Application
{
public:
    Application(HINSTANCE hInstance = NULL);
    ~Application();

    // Initialize OpenGL graphics
    void InitializeGfx();

    // Load OpenGL extension functions
    void LoadOpenGLFunctions();

    std::shared_ptr<OglWindow> CreateOglWindow();

    void Init();
    void Start();

    void Destroy();

    void BuildProgram();
    std::shared_ptr<const Program> GetProgram() const { return m_program; }

private:
    // Platform-specific application info
    HINSTANCE m_hInstance;

    Game m_game;
    std::shared_ptr<HumanGameView> m_view;
    std::shared_ptr<Program> m_program;
};

extern Application g_app;

#endif
