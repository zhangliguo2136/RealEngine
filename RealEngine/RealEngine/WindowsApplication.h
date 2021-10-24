#pragma once

#include <windows.h>
#include <windowsx.h>
#include <iostream>
#include "BaseApplication.h"

namespace RealEngine {
	class WindowsApplication :public BaseApplication 
	{
	public:
		WindowsApplication()
			:BaseApplication() {};

		virtual int Initialize() override;
		virtual void Finalize() override;
		virtual void Tick() override;

		static LRESULT CALLBACK WindowProc(HWND hWnd,
			UINT message,
			WPARAM wParam,
			LPARAM lParam);
	};
}