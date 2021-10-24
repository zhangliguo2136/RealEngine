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

		// ��������
		int createWindow(int width, int height, const char* winName);
	private:
		// ���ڴ�С�����ص�
		static void onFrameBufferSizeCallback(GLFWwindow* window, int width, int height);
		// ���̻ص�
		static void onKeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		// ���ص�
		static void onMouseCallback(GLFWwindow* window, int button, int action, int mods);
		// ָ��λ�ûص�
		static void onCursorCallback(GLFWwindow* window, double x, double y);
		//���ֻص�
		static void onScrollCallback(GLFWwindow* window, double x, double y);
		// ���������ڵĻص�
		static void onCursorEnterCallback(GLFWwindow* window, int enterd);

		// ���ڹرյĻص�
		static void onCloseCallback(GLFWwindow* window);
	private:
		GLFWwindow* pWindows;
		int m_width;
		int m_height;
		std::string m_name;
	};
}
