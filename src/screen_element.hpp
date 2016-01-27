#ifndef _SCREEN_ELEMENT_HPP_
#define _SCREEN_ELEMENT_HPP_

class IScreenElement
{
public:
    // TODO: Restore? When screen/device is lost

    virtual void Render(long deltaMs) = 0;
    virtual void Update(long deltaMs) = 0;
    // TODO: Z-order?
    // TODO: Visibility?

    // TODO: Message processing ~ virtual void ProcessMessage(AppMsg msg) = 0;
};

#endif
