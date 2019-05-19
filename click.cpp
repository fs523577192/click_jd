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

class ClickHelper
{
private:
	POINT screenEdge;

public:
	ClickHelper()
	{
		this->screenEdge.x = GetSystemMetrics(SM_CXSCREEN);
		this->screenEdge.y = GetSystemMetrics(SM_CYSCREEN);
	}

	void clickAt(int x, int y)
	{
		int dx = x * 65536 / this->screenEdge.x;
		int dy = y * 65536 / this->screenEdge.y;
		
		MouseInput move(dx, dy, MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE);
		move.sendInput();
		
		MouseInput mouseDown(dx, dy, MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTDOWN);
		mouseDown.sendInput();
		
		MouseInput mouseUp(dx, dy, MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTUP);
		mouseUp.sendInput();
	}
};

class DragHelper
{
private:
	POINT screenEdge;

public:
	DragHelper()
	{
		this->screenEdge.x = GetSystemMetrics(SM_CXSCREEN);
		this->screenEdge.y = GetSystemMetrics(SM_CYSCREEN);
	}

	void drag(int fromX, int fromY, int toX, int toY)
	{
		int x1 = fromX * 65536 / this->screenEdge.x;
		int y1 = fromY * 65536 / this->screenEdge.y;
		int x2 = toX * 65536 / this->screenEdge.x;
		int y2 = toY * 65536 / this->screenEdge.y;
		
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