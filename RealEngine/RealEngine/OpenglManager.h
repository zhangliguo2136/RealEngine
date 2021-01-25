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

		// 创建窗口
		int createWindow(int width, int height, const char* winName);
	private:
		// 窗口大小调整回调
		static void onFrameBufferSizeCallback(GLFWwindow* window, int width, int height);
		// 键盘回调
		static void onKeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		// 鼠标回调
		static void onMouseCallback(GLFWwindow* window, int button, int action, int mods);
		// 指针位置回调
		static void onCursorCallback(GLFWwindow* window, double x, double y);
		//滚轮回调
		static void onScrollCallback(GLFWwindow* window, double x, double y);

		// 窗口关闭的回调
		static void onCloseCallback(GLFWwindow* window);
	private:
		GLFWwindow* pWindows;
		int width;
		int height;
	};
}
