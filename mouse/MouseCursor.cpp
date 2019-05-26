#ifndef __MOUSE_CURSOR__
#define __MOUSE_CURSOR__

#include <Windows.h>

class MouseCursor
{
private:
    POINT point;
    
public:
    MouseCursor()
    {
        GetCursorPos(&this->point);
    }
    
    int getX()
    {
        return this->point.x;
    }
    
    int getY()
    {
        return this->point.y;
    }
};
#endif // __MOUSE_CURSOR__
