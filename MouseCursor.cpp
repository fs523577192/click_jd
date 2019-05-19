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