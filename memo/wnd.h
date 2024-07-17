#ifndef _wnd_h
#define _wnd_h

//typedef int bool;
#define True 1
#define False 0
#define CFUNC extern "C"


//////////////////////////////////////
//ウインドウの抽象化のための仮想クラス
class VWin
{
protected:
	HWND handle;

public:
	VWin()
	{
		handle=0;
	}

	HWND getHandle()
	{
		return handle;
	}

protected:
	void setHandle(HWND h)
	{
		handle=h;
	}
};

///////////////////////////////////////////
//
class Wnd : public VWin
{
	static bool register_flag;

protected:
	virtual bool RegisterFlag();
	virtual void RegisterClass();
	bool RegisteredP();

public:
	Wnd();
	virtual ~Wnd();
	virtual void OpenWindow();
	virtual void Update();
/*
	operator void *()
	{
		return (!handle) ? : this;
	}
*/
	virtual long WindowProc(UINT msg, WPARAM wparam, LPARAM lparam);
	HDC getDC();
	void releaseDC(HDC dc);
};
/////////////////////////////////////////////////////////////////
CFUNC long CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

class Paint
{
	PAINTSTRUCT ps;
	HWND h;
	HDC dc;
public:
	Paint(HWND h);
	~Paint();
	HDC getDC()
	{
		return dc;
	}
};

//////////////////////////////////////////////////////////////////
int Main(void);

class MSWin
{
	static HANDLE instance;
	static HANDLE prev_instance;
	static LPSTR cmd_line;
	static int cmd_show;
public:
	MSWin(HANDLE instance, HANDLE prev_instance, LPSTR cmd_line, int cmd_show);
	static int MessageLoop();
	static HANDLE getInstance()
	{
		return instance;
	}
	static LPSTR getCmdLine()
	{
		return cmd_line;
	}
	static int getCmdShow()
	{
		return cmd_show;
	}
};

#endif

