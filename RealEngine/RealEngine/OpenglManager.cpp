#include "OpenglManager.h"
#include <iostream>

int RealEngine::OpenglManager::createWindow(int width, int height, const char* winName)
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

	glfwSetFramebufferSizeCallback(pWindows, onFrameBufferSizeCallback);
	glfwSetKeyCallback(pWindows, onKeyboardCallback);
	glfwSetCursorPosCallback(pWindows, onCursorCallback);
	glfwSetMouseButtonCallback(pWindows, onMouseCallback);
	glfwSetScrollCallback(pWindows, onScrollCallback);
	glfwSetWindowCloseCallback(pWindows, onCloseCallback);
}
void RealEngine::OpenglManager::onFrameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void RealEngine::OpenglManager::onKeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	printf("onKeyboardInput: key is %d, action is %d", key, action);
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

void RealEngine::OpenglManager::onMouseCallback(GLFWwindow* window, int button, int action, int mods) 
{
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
void RealEngine::OpenglManager::onCursorCallback(GLFWwindow* window, double x, double y) 
{
	return;
}
//滚轮回调
void RealEngine::OpenglManager::onScrollCallback(GLFWwindow* window, double x, double y) 
{
	return;
}

// 窗口关闭的回调
void RealEngine::OpenglManager::onCloseCallback(GLFWwindow* window) 
{
	glfwSetWindowShouldClose(window, GL_TRUE);
}
