#ifndef __MOUSE_INPUT__
#define __MOUSE_INPUT__

#include <Windows.h>
#include <tchar.h>

class MouseInput
{
private:
    INPUT input;

public:
    MouseInput(int x, int y, int dwFlags)
    {
        input.type = INPUT_MOUSE;
        input.mi.dx = x;
        input.mi.dy = y;
        input.mi.mouseData = 0;
        input.mi.dwFlags = dwFlags;
        input.mi.time = 0;
        input.mi.dwExtraInfo = 0;
    }

    void sendInput()
    {
        SendInput(1, &input, sizeof(INPUT));
    }
};
#endif // __MOUSE_INPUT__
