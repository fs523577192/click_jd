#ifndef __GDC__
#define __GDC__

#include "WindowRegion.cpp"

class GraphicalDeviceContextInMem
{
private:
    HDC hDC;
    BITMAP bitmap;
    HBITMAP hBitmap = NULL;
    HBITMAP hOriginalBitmap = NULL;

public:
    GraphicalDeviceContextInMem(HDC hDC, WindowRegion *pRegion)
    {
        this->hDC = CreateCompatibleDC(hDC);
        if (!this->hDC) {
            throw TEXT("Fail to CreateCompatibleDC from an HDC");
        }

        this->hBitmap = CreateCompatibleBitmap(hDC, pRegion->getWidth(), pRegion->getHeight());
        if (!this->hBitmap) {
            DeleteDC(this->hDC);
            throw TEXT("Fail to CreateCompatibleBitmap");
        }

        this->hOriginalBitmap = (HBITMAP) SelectObject(this->hDC, this->hBitmap);

        if (!BitBlt(this->hDC, 0, 0, pRegion->getWidth(), pRegion->getHeight(),
                hDC, 0, 0, SRCCOPY)) {
            DeleteObject(this->hBitmap);
            DeleteDC(this->hDC);
            throw TEXT("Fail to transfer bit blocks into the compatible memory DC");
        }

        if (!GetObject(this->hBitmap, sizeof(BITMAP), &this->bitmap)) {
            DeleteObject(this->hBitmap);
            DeleteDC(this->hDC);
            throw TEXT("Fail to get the BITMAP from the HBITMAP");
        }
    }

    ~GraphicalDeviceContextInMem()
    {
        if (NULL != this->hBitmap) {
            DeleteObject(this->hBitmap);
        }
        DeleteDC(this->hDC);
    }


};

class GraphicalDeviceContextInWindow
{
private:
    HWND hwnd;
    HDC hDC;
    WindowRegion *pRegion;

public:
    GraphicalDeviceContextInWindow(HWND hwnd)
    {
        this->hwnd = hwnd;
        this->hDC = GetDC(hwnd);
        if (!this->hDC) {
            throw TEXT("Fail to GetDC of an HWND");
        }
        this->pRegion = new WindowRegion(hwnd);
    }

    ~GraphicalDeviceContextInWindow()
    {
        delete this->pRegion;
        ReleaseDC(this->hwnd, this->hDC);
    }

    GraphicalDeviceContextInMem *getInMem()
    {
        return new GraphicalDeviceContextInMem(this->hDC, this->pRegion);
    }

    WindowRegion *getWindowRegion()
    {
        return this->pRegion;
    }
};
#endif // __GDC__
