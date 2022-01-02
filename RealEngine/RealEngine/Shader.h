#pragma once
#include <string>

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

#include "NonCopyable.h"
#include "Matrix.h"

class Shader :public NonCopyable
{
public:
	Shader() {};
	virtual ~Shader();

	Shader(const std::string &vertexFile, const std::string &fragmentFile);
	void useProgram() const;

	void setMatrixUniform(const char* name, Matrix4* mat4);

	void setUniform1i(const char* name, unsigned int i);
protected:
	GLuint m_id;
};