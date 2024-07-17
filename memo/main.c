#include <windows.h>


LRESULT CALLBACK WindowFunc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message){
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd,message,wParam,lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	HWND hwnd;
	MSG msg;
	WNDCLASSEX wcl;

	wcl.cbSize=sizeof(WNDCLASSEX);
	wcl.hInstance=hInstance;
	wcl.lpszClassName="MyWin";
	wcl.lpfnWndProc=WindowFunc;
	wcl.style=0;
	wcl.hIcon=LoadIcon(NULL, IDI_APPLICATION);
	wcl.hIconSm=LoadIcon(NULL,IDI_WINLOGO);
	wcl.hCursor=LoadCursor(NULL,IDC_ARROW);
	wcl.lpszMenuName=NULL;
	wcl.cbClsExtra=0;
	wcl.cbWndExtra=0;
	wcl.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
	if(!RegisterClassEx(&wcl)){
		MessageBox(NULL,"RegisterClassExにエラーがでた","エラー",MB_OK);
		return 0;
	}
	hwnd=CreateWindow(
		wcl.lpszClassName,
		"Skeleton",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		HWND_DESKTOP,
		NULL,
		hInstance,
		NULL
		);
	ShowWindow(hwnd,nShowCmd);
	UpdateWindow(hwnd);
	while(GetMessage(&msg,NULL,0,0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

