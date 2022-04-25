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

	Shader(const std::string &vertexFile, const std::string &fragmentFile, const std::string &geomFile = "");

	void useProgram() const;

	void setUniformMatrix4fv(const char* name, float* data);

	void setUniform1i(const char* name, unsigned int i);

	void setUniform3fv(const char* name, float* data);

	void setUniform4fv(const char* name, float* data);

	unsigned int getShaderID() 
	{
		return m_id;
	};
protected:
	GLuint m_id;
};