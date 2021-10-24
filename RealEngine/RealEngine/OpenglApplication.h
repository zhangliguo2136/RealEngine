#pragma once
#include "BaseApplication.h"

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

#include <string>

namespace RealEngine 
{
	class OpenglApplication :public BaseApplication
	{
	public:
		virtual int Initialize() override;
		virtual void Finalize() override;
		virtual void Tick() override;

		static OpenglApplication& getInstance()
		{
			static OpenglApplication s_sInstance;
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
		// 鼠标进出窗口的回调
		static void onCursorEnterCallback(GLFWwindow* window, int enterd);

		// 窗口关闭的回调
		static void onCloseCallback(GLFWwindow* window);
	private:
		GLFWwindow* pWindows;
		int m_width;
		int m_height;
		std::string m_name;
	};
}
