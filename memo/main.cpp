#include <windows.h>
#include "wnd.h"

class MyWnd : public Wnd
{
	virtual long WindowProc(UINT msg, WPARAM wparam, LPARAM lparam);
	public:
};

long MyWnd::WindowProc(UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch(msg)
	{
	case WM_PAINT:
		Paint pnt(getHandle());
		::TextOut(pnt.getDC(),10,10,"hello,world",12);
		break;
	default:
		return Wnd::WindowProc(msg,wparam,lparam);
	}
	return 0;
}

int Main(){
	MyWnd mywnd;
	mywnd.OpenWindow();
	return MSWin::MessageLoop();
}

