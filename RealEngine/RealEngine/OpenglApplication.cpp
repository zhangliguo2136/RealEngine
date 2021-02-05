#include "OpenglApplication.h"
#include "OpenglDriver.h"

#include <iostream>
#include "Logger.h"

using namespace RealEngine;

namespace RealEngine
{
	OpenglApplication g_App;
	IApplication* g_pApp = &g_App;
}

int RealEngine::OpenglApplication::Initialize() 
{
	int result = BaseApplication::Initialize();

	if (result != 0)
	{
		printf("WindowApplication:Initialize faild, will be exit.");
		exit(result);
	}

	createWindow(800, 600, "RealEngine::OpenglApplication");

	return result;
}
void RealEngine::OpenglApplication::Finalize() 
{
	BaseApplication::Finalize();
}
void RealEngine::OpenglApplication::Tick() 
{
	BaseApplication::Tick();

	glfwSwapBuffers(pWindows);
	glfwPollEvents();
}

int RealEngine::OpenglApplication::createWindow(int width, int height, const char* winName)
{
	width = width;
	height = height;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	pWindows = glfwCreateWindow(width, height, winName, NULL, NULL);

	if (pWindows == nullptr) 
	{
		std::cout<< "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(pWindows);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glfwSetFramebufferSizeCallback(pWindows, onFrameBufferSizeCallback);
	glfwSetKeyCallback(pWindows, onKeyboardCallback);
	glfwSetCursorPosCallback(pWindows, onCursorCallback);
	glfwSetMouseButtonCallback(pWindows, onMouseCallback);
	glfwSetScrollCallback(pWindows, onScrollCallback);
	glfwSetWindowCloseCallback(pWindows, onCloseCallback);

	return 0;
}
void RealEngine::OpenglApplication::onFrameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
	//glViewport(0, 0, width, height);
}

void RealEngine::OpenglApplication::onKeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	log("onKeyboardInput: key is %d, action is %d\n", key, action);

	switch (action)
	{
	case GLFW_PRESS:
		break;
	case GLFW_RELEASE:
		break;
	case GLFW_REPEAT:
		break;
	}

	switch (key)
	{
	case GLFW_KEY_ESCAPE:
		onCloseCallback(window);
		break;
	}
}

void RealEngine::OpenglApplication::onMouseCallback(GLFWwindow* window, int button, int action, int mods) 
{

	log("onMouseCallback: the button is %d, action is %d\n", button, action);

	switch (action)
	{
	case GLFW_PRESS:
		break;
	case GLFW_RELEASE:
		break;
	case GLFW_REPEAT:
		break;
	}

	switch (button) 
	{
	case GLFW_MOUSE_BUTTON_LEFT:
		break;
	case GLFW_MOUSE_BUTTON_MIDDLE:
		break;
	case GLFW_MOUSE_BUTTON_RIGHT:
		break;
	}
}

// 指针位置回调
void RealEngine::OpenglApplication::onCursorCallback(GLFWwindow* window, double x, double y) 
{
	return;
}
//滚轮回调
void RealEngine::OpenglApplication::onScrollCallback(GLFWwindow* window, double x, double y) 
{
	return;
}

// 窗口关闭的回调
void RealEngine::OpenglApplication::onCloseCallback(GLFWwindow* window) 
{
	log("OpenglApplication::onCloseCallback()----------------------\n");

	BaseApplication::m_bQuit = true;
}
