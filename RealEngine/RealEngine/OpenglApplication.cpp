#include "OpenglApplication.h"
#include "OpenglDriver.h"
#include "InputManager.h"
#include "RealEngine.h"

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

	EConfig config;
	m_width = config.Width;
	m_height = config.Height;
	m_name = config.Name;

	createWindow(config.Width, config.Height, config.Name.c_str());

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

int RealEngine::OpenglApplication::createWindow(int inWidth, int inHeight, const char* winName)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	pWindows = glfwCreateWindow(m_width, m_height, winName, NULL, NULL);

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
	glfwSetCursorEnterCallback(pWindows, onCursorEnterCallback);
	glfwSetWindowCloseCallback(pWindows, onCloseCallback);

	return 0;
}
void RealEngine::OpenglApplication::onFrameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
	//glViewport(0, 0, width, height);
}

void RealEngine::OpenglApplication::onKeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Log("onKeyboardInput: key is %d, action is %d\n", key, action);

	auto& inputManager = InputManager::getInstance();

	switch (action)
	{
	case GLFW_PRESS:
		inputManager.InputKeyDown(key);
		break;
	case GLFW_RELEASE:
		inputManager.InputKeyUp(key);
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

	Log("onMouseCallback: the button is %d, action is %d\n", button, action);

	auto& inputManager = InputManager::getInstance();

	switch (action)
	{
	case GLFW_PRESS:
		inputManager.InputKeyDown(button);
		break;
	case GLFW_RELEASE:
		inputManager.InputKeyUp(button);
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
	Log("OpenglApplication:: the cursor pos x, y (%f, %f)\n", x, y);

	auto& inputManager = InputManager::getInstance();
	inputManager.InputCursor(x, y);

	return;
}
//滚轮回调
void RealEngine::OpenglApplication::onScrollCallback(GLFWwindow* window, double x, double y) 
{
	Log("OpenglApplication:: the scroll pos x, y (%f, %f)\n", x, y);

	auto& inputManager = InputManager::getInstance();
	inputManager.InputScroll(x, y);

	return;
}

void RealEngine::OpenglApplication::onCursorEnterCallback(GLFWwindow* window, int enterd)
{
	Log("OpenglApplication::onCursorEnterCallback the enterd is %d\n", enterd);

	auto& inputManager = InputManager::getInstance();

	switch (enterd)
	{
	// ENTER
	case GLFW_TRUE: 
		inputManager.InputCursorEnter(true);
		break;
	// LEAVE
	case GLFW_FALSE: 
		inputManager.InputCursorEnter(false);
		break;
	}

	return;
}

// 窗口关闭的回调
void RealEngine::OpenglApplication::onCloseCallback(GLFWwindow* window) 
{
	Log("OpenglApplication::onCloseCallback()----------------------\n");

	BaseApplication::m_bQuit = true;
}
