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

class Window
{
private:
	WNDCLASSEX wndClass;
	HWND hwnd;
	
public:

	const static int DEFAULT = CW_USEDEFAULT;
	
	Window(HWND hwnd)
	{
		this->hwnd = hwnd;
	}
	
	Window(HINSTANCE hInstance, LPCTSTR className,
			LPCTSTR windowName, WNDPROC WndProc,
			int x, int y, int width, int height)
	{
		if (!registerClass(hInstance, className, WndProc)) {
			throw TEXT("Fail to RegisterClass");
		}

		this->hwnd = CreateWindow(
                className,                 //窗口类名
                windowName,                //窗口标题
                WS_OVERLAPPEDWINDOW,       //窗口的风格
                x, y, width, height,
                NULL,                      //父窗口:无
                NULL,                      //子菜单:无
                hInstance,                 //该窗口应用程序的实例句柄 
                NULL                       //
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
        while ( GetMessage(&msg, NULL, 0, 0) ) {
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
		this->wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		this->wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
		this->wndClass.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
		this->wndClass.lpszMenuName = NULL;
		this->wndClass.lpszClassName = className;
		this->wndClass.hIconSm = NULL;
		
		if ( !RegisterClassEx(&this->wndClass) ) {
			return FALSE;
		}
		return TRUE;
	}
};