#pragma once
#include "IRuntimeModule.h"

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

namespace RealEngine 
{
	class OpenglManager :public IRuntimeModule
	{
	public:
		virtual int Initialize() {};
		virtual void Finalize() {};
		virtual void Tick() {};

		static OpenglManager& getInstance()
		{
			static OpenglManager s_sInstance;
			return s_sInstance;
		}

		// ´´½¨´°¿Ú
		int createWindow(int width, int height, const char* winName);

	private:
		void processInput();

	private:
		GLFWwindow* pWindows;
		int width;
		int height;
	};
}
