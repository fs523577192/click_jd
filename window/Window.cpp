#ifndef __H_WINDOW__
#define __H_WINDOW__

#include "../log/Logger.cpp"
#include "GraphicalDeviceContext.cpp"

class Window
{
private:
    WNDCLASSEX wndClass;
    HWND hwnd;
    Logger *pLogger;
    
public:

    const static int DEFAULT = CW_USEDEFAULT;
    
    Window(HWND hwnd, Logger *pLogger)
    {
        this->hwnd = hwnd;
        this->pLogger = pLogger;

        TCHAR buffer[20];
        _stprintf(buffer, TEXT("Window HWND: %X"), hwnd);
        pLogger->info(buffer);
    }
    
    Window(HINSTANCE hInstance, LPCTSTR className,
            LPCTSTR windowName, WNDPROC WndProc,
            int x, int y, int width, int height,
            Logger *pLogger)
    {
        this->pLogger = pLogger;

        if (!registerClass(hInstance, className, WndProc)) {
            throw TEXT("Fail to RegisterClass");
        }

        this->hwnd = CreateWindow(
                className,                 //窗口类名
                windowName,                //窗口标题
                WS_OVERLAPPEDWINDOW,       //窗口的风格
                x, y, width, height,
                nullptr,                   //父窗口:无
                nullptr,                   //子菜单:无
                hInstance,                 //该窗口应用程序的实例句柄 
                nullptr                    //
        );
    }
    
    void show(int nCmdShow)
    {
        ShowWindow(this->hwnd, nCmdShow);
    }
    
    void update()
    {
        UpdateWindow(this->hwnd);
    }
    
    void showOnTop()
    {
        SetWindowPos(this->hwnd, HWND_TOP,
                0, 0, 0, 0,
                SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
    }
    
    void getDisplayContent()
    {
        GraphicalDeviceContextInWindow gdcWin(this->hwnd);
        gdcWin.getInMem();
    }
    
    int messageLoop()
    {
        MSG msg;
        while ( GetMessage(&msg, nullptr, 0, 0) ) {
            TranslateMessage(&msg);                 //将虚拟键消息转换为字符消息
            DispatchMessage(&msg);                  //分发到回调函数(过程函数)
        }
        return msg.wParam;
    }

private:
    BOOL registerClass(HINSTANCE hInstance,
            LPCTSTR className,
            WNDPROC WndProc)
    {
        this->wndClass.cbSize = sizeof(WNDCLASSEX);
        this->wndClass.style = CS_HREDRAW | CS_VREDRAW;
        this->wndClass.lpfnWndProc = WndProc;
        this->wndClass.cbWndExtra = 0;
        this->wndClass.cbClsExtra = 0;
        this->wndClass.hInstance = hInstance;
        this->wndClass.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
        this->wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
        this->wndClass.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
        this->wndClass.lpszMenuName = nullptr;
        this->wndClass.lpszClassName = className;
        this->wndClass.hIconSm = nullptr;
        
        if ( !RegisterClassEx(&this->wndClass) ) {
            return FALSE;
        }
        return TRUE;
    }
};
#endif // __H_WINDOW__
