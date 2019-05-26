#ifndef __CLICK_HELPER__
#define __CLICK_HELPER__

#include "MouseInput.cpp"
#include "../window/ScreenSize.cpp"
#include "../log/Logger.cpp"

class ClickHelper
{
private:
    ScreenSize *pScreenSize;
    Logger *pLogger;

public:
    ClickHelper(ScreenSize *pScreenSize, Logger *pLogger)
    {
        this->pScreenSize = pScreenSize;
        this->pLogger = pLogger;
    }

    void clickAt(int x, int y)
    {
        int xx = x * 65536, yy = y * 65536;
        int dx = xx / (this->pScreenSize->getWidth());
        int dy = yy / (this->pScreenSize->getHeight());

        TCHAR buffer[50];
        _stprintf(buffer, TEXT("Click: (%d, %d) * 65536 = (%d, %d)"), x, y, xx, yy);
        pLogger->info(buffer);
        _stprintf(buffer, TEXT("Click: (%d, %d) / (%d, %d) = (%d, %d)"), xx, yy,
                this->pScreenSize->getWidth(), this->pScreenSize->getHeight(), dx, dy);
        pLogger->info(buffer);

        MouseInput move(dx, dy, MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE);
        move.sendInput();
        
        MouseInput mouseDown(dx, dy, MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTDOWN);
        mouseDown.sendInput();
        
        MouseInput mouseUp(dx, dy, MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTUP);
        mouseUp.sendInput();
    }
};
#endif // __CLICK_HELPER__
