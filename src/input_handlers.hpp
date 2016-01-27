#ifndef _INPUT_HANDLERS_HPP_
#define _INPUT_HANDLERS_HPP_

class KeyboardHandler
{
    virtual bool OnKeyDown(const unsigned int keyCode) = 0;
    virtual bool OnKeyUp(const unsigned int keyCode) = 0;
};

class MouseHandler
{
    virtual bool OnLMouseDown(const int x, const int y) = 0;
    virtual bool OnLMouseUp(const int x, const int y) = 0;
    virtual bool OnRMouseDown(const int x, const int y) = 0;
    virtual bool OnRMouseUp(const int x, const int y) = 0;
    virtual bool OnMouseMove(const int x, const int y) = 0;
};

#endif
