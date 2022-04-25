#include "WindowsApplication.h"
#include <tchar.h>
#include "InputManager.h"
#include "RealEngine.h"

using namespace RealEngine;

//namespace RealEngine 
//{
//	WindowsApplication g_App;
//	IApplication* g_pApp = &g_App;
//}

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

	EConfig config;

	hWnd = CreateWindowEx(0,
		_T(config.Name.c_str()),
		_T(config.Name.c_str()),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		config.Width,
		config.Height,
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
	InputManager& pManager = InputManager::getInstance();

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
	break;
	case WM_LBUTTONDOWN:
	{
		pManager.InputKeyDown(wParam);
	}
	break;
	case WM_LBUTTONUP:
	{
		pManager.InputKeyUp(wParam);
	}
	break;
	case WM_RBUTTONDOWN:
	{
		pManager.InputKeyDown(wParam);
	}
	break;
	case WM_RBUTTONUP:
	{
		pManager.InputKeyUp(wParam);
	}
	break;
	case WM_KEYDOWN:
	{
		pManager.InputKeyDown(wParam);
	}
	break;
	case WM_KEYUP:
	{
		pManager.InputKeyUp(wParam);
	}
	break;
	case WM_MOUSEMOVE:
	{
		pManager.InputCursor(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
	}
	break;
	case WM_MOUSEWHEEL:
	{
		printf("%hd\n", (int)GET_WM_VSCROLL_POS(wParam, lParam));
	}
	break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}