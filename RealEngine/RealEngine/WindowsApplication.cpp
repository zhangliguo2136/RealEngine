#include "WindowsApplication.h"
#include <tchar.h>
using namespace RealEngine;

namespace RealEngine 
{
	BaseApplication g_App;
	IApplication* g_pApp = &g_App;
}

int RealEngine::WindowsApplication::Initialize()
{
	int result = BaseApplication::Initialize();

	if (result != 0) 
	{
		printf("WindowApplication:Initialize faild, will be exit.");
		exit(result);
	}

	HINSTANCE hInstance = GetModuleHandle(NULL);

	HWND hWnd;
	WNDCLASSEX wc;

	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = _T("RealEngine");

	RegisterClassEx(&wc);

	hWnd = CreateWindowEx(0,
		_T("RealEngine"),
		_T("RealEngine"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		1920,
		1080,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hWnd, SW_SHOW);
	
	return result;
}

void RealEngine::WindowsApplication::Finalize()
{
	BaseApplication::Finalize();
}

void RealEngine::WindowsApplication::Tick()
{
	BaseApplication::Tick();

	MSG msg;

	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) 
	{
		TranslateMessage(&msg);

		DispatchMessage(&msg);
	}
}

LRESULT CALLBACK RealEngine::WindowsApplication::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) 
{
	switch (message)
	{
	case WM_PAINT:
		{
			
		}
		break;
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			BaseApplication::m_bQuit = true;

			return 0;
		}
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}