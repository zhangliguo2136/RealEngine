#pragma once
#include <string>

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

#include "NonCopyable.h"

class Shader :public NonCopyable
{
public:
	Shader() {};
	virtual ~Shader();

	Shader(const std::string &vertexFile, const std::string &fragmentFile);
	void useProgram() const;

	void setMatrixUniform(const char* name, const GLfloat* mat4);

protected:
	GLuint m_id;
};