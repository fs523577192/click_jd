#ifndef __SCREEN_SIZE__
#define __SCREEN_SIZE__

#include <Windows.h>
#include "../log/Logger.cpp"

class ScreenSize
{
private:
    int width, height;

public:
    ScreenSize(Logger *pLogger)
    {
        this->width = GetSystemMetrics(SM_CXSCREEN);
        this->height = GetSystemMetrics(SM_CYSCREEN);

        TCHAR buffer[30];
        _stprintf(buffer, TEXT("ScreenSize: (%d, %d)"), this->width, this->height);
        pLogger->info(buffer);
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
#endif // __SCREEN_SIZE__
