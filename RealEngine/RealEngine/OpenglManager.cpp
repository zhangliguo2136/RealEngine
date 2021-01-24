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
}
