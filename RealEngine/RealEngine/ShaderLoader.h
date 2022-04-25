#pragma once

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

#include <string>

GLuint loadShaders(const std::string &vertexShader,
	const std::string &fragmentShader, const std::string &geomShader = nullptr);