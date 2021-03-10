#pragma once
#include <string>

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

#include "NonCopyable.h"

class Shader :public NonCopyable
{
public:
	Shader(const std::string &vertexFile, const std::string &fragmentFile);

	virtual ~Shader();

	void useProgram() const;

protected:
	GLuint m_id;
};