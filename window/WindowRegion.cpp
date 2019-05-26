#ifndef __WINDOW_REGEION__
#define __WINDOW_REGEION__

#include <Windows.h>
#include <tchar.h>

class WindowRegion
{
private:
    RECT rect;
    unsigned int width, height;

public:
    WindowRegion(HWND hwnd)
    {
        GetWindowRect(hwnd, &this->rect);
        this->width = this->rect.right - this->rect.left;
        this->height = this->rect.bottom - this->rect.top;
    }

    int getLeft()
    {
        return this->rect.left;
    }

    int getRight()
    {
        return this->rect.right;
    }

    int getTop()
    {
        return this->rect.top;
    }

    int getBottom()
    {
        return this->rect.bottom;
    }

    int getWidth()
    {
        return this->width;
    }

    int getHeight()
    {
        return this->height;
    }
};
#endif // __WINDOW_REGION__
