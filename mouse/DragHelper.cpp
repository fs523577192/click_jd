#ifndef __DRAG_HELPER__
#define __DRAG_HELPER__

#include "MouseInput.cpp"
#include "../window/ScreenSize.cpp"
#include "../log/Logger.cpp"

class DragHelper
{
private:
    ScreenSize *pScreenSize;
    Logger *pLogger;

public:
    DragHelper(ScreenSize *pScreenSize, Logger *pLogger)
    {
        this->pScreenSize = pScreenSize;
        this->pLogger = pLogger;
    }

    void drag(int fromX, int fromY, int toX, int toY)
    {
        int x1 = (fromX * 65536) / (this->pScreenSize->getWidth());
        int y1 = (fromY * 65536) / (this->pScreenSize->getHeight());
        int x2 = (toX * 65536) / (this->pScreenSize->getWidth());
        int y2 = (toY * 65536) / (this->pScreenSize->getHeight());

        TCHAR buffer[40];
        _stprintf(buffer, TEXT("Drag: (%d, %d) to (%d, %d)"), x1, y1, x2, y2);
        pLogger->info(buffer);

        MouseInput move1(x1, y1, MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE);
        move1.sendInput();

        MouseInput mouseDown(x1, y1, MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTDOWN);
        mouseDown.sendInput();

        MouseInput move2(x2, y2, MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE);
        move2.sendInput();

        MouseInput mouseUp(x2, y2, MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTUP);
        mouseUp.sendInput();
    }
};
#endif // __DRAG_HELPER__
