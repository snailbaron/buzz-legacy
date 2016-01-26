#include "game_window.hpp"

LRESULT GameWindow::WinProc(UINT msg, WPARAM wparam, LPARAM lparam)
{
    switch (msg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }
    return Window::WinProc(msg, wparam, lparam);
}
