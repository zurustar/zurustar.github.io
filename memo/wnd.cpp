#include <windows.h>
#include "wnd.h"


static char* win_class_name = "Wnd";

bool Wnd::register_flag = False;

bool Wnd::RegisteredP()
{
	return MSWin::GetPrevInstance() || RegisterFlag();
}

bool Wnd::RegisterFlag()
{
	return register_flag;
}

void Wnd::RegisterClass()
{
	if(RegisteredP())
	{
		return;
	}
	WNDCLASS wcClass;
	wcClass.lpszClassName=win_class_name;
	wcClass.hInstance=MSWin::GetInstance();
	wcClass.lpfnWndProc=::WindowProc;
	wcClass.hCursor=LoadCursor(NULL,IDC_ARROW);
	wcClass.hIcon=LoadIcon(MSWin::GetInstance(),IDI_APPLICATION);
	wcClass.lpszMenuName=(LPSTR)NULL;
	wcClass.hbrBackground=GetStockObject(WHITE_BRUSH);
	wcClass.style=CS_HREDRAW|CS_VREDRAW;
	wcClass.cbClsExtra=0;
	wcClass.cbWndExtra=sizeof(Wnd*);
	::RegisterClass(&wcClass);
	register_flag=True;
}

Wnd::Wnd()
{
}

Wnd::~Wnd()
{
}

void Wnd::OpenWindow()
{
	RegisterClass();
	SetHandle(::CreateWindow(win_class_name,win_class_name,WS_OVERLAPPEDWINDOW|WS_MAXIMIZEBOX|WS_MINIMIZEBOX,CW_USEDEFAULT,0,CW_USEDEFAULT,0,NULL,NULL,MSWin::GetInstance(),(LPSTR)this));
	Update();
}

void Wnd::Update()
{
	::ShowWindow(GetHandle(),MSWin::GetCmdShow());
	::UpdateWindow(GetHandle());
}

long Wnd::WindowProc(UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch(msg)
	{
	case WM_DESTROY:
		::PostQuitMessage(0);
		break;
	default:
		return ::DefWindowProc(handle,msg,wparam,lparam);
	}
	return 0L;
}

CFUNC long CALLBACK WindowProc(HWND handle, UINT msg, WPARAM wparam, LPARAM lparam)
{
	#if defined (__SMALL__) || defined (__MEDIUM__)
		Wnd* wd=(Wnd*)::GetWindowWord(handle,0);
	#endif
	#if defined (__LARGE__) || defined (__COMPACT__)
		Wnd* wd=(Wnd*)::GetWindowLong(handle,0);
	#endif
	if(wd==0)
	{
		if(msg==WM_CREATE)
		{
			LPCREATESTRUCT lpcs;
			lpcs=(LPCREATESTRUCT)lparam;
			wd=(Wnd*)lpcs->lpCreateParams;
			#if defined (__SMALL__) || defined (__MEDIUM__)
				::SetWindowWord(handle,0);
			#endif
			#if defined (__LARGE__) || defined (__COMPACT__)
				::SetWindowLong(handle,0);
			#endif
		}
		else
		{
			return ::DefWindowProc(handle,msg,wparam,lparam);
		}
	}
	return wd->WindowProc(msg,wparam,lparam);
}

HDC Wnd::getDC()
{
	return ::getDC(getHandle());
}

void Wnd::releaseDC(HDC dc)
{
	::ReleaseDC(GetHandle(),dc);
}
////////////////////////////////////////////////////////////
Paint::Paint(HWND h)
{
	Paint::h=h;
	dc=::BeginPaint(h,&ps);
}

Paint::~Paint()
{
	::EndPaint(h,&ps);
}


////////////////////////////////////////////////////////////


CFUNC int PASCAL WinMain(HANDLE instance, HANDLE prev_instance, LPSTR cmd_line, int show)
{
	MSWin main(instance, prev_instance, cmd_line,show);
	return Main();
}

HANDLE MSWin::instance=0;
HANDLE MSWin::prev_instance=0;
LPSTR MSWin::cmd_line = 0;
int MSWin::cmd_show=0;

MSWin::MSWin(HANDLE instance, HANDLE prev_instance, LPSTR cmd_line, int cmd_show)
{
	MSWin::instance=instance;
	MSWin::prev_instance=prev_instance;
	MSWin::cmd_line=cmd_line;
	MSWin::cmd_show=cmd_show;
}

int MSWin::MessageLoop()
{
	MSG msg;
	while(::GetMessage(&msg,NULL,0,0))
	{
		::TranslateMessage(&msg);
		::DispatchMessage(&msg);
	}
	return msg.wParam;
}

