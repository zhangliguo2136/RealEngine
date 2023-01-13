#pragma once
#pragma once
#include <string>

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

#include "NonCopyable.h"

enum GLShaderType
{
	SHADER_VERTEX,
	SHADER_FRAGMENT,
	SHADER_GEOMETRY,
	SHADER_COMPUTE
};

class GLProgram :public NonCopyable
{
public:
	GLProgram();
	~GLProgram();

	void AttachProgram(const std::string&, GLShaderType);

	void LinkProgram();

	void UseProgram() const;

	void Dispatch(int x = 1, int y = 1, int z = 1);

	void setUniformMatrix4fv(const char* name, float* data);

	void setUniform1i(const char* name, unsigned int i);

	void setUniform2fv(const char* name, float* data);

	void setUniform3fv(const char* name, float* data);

	void setUniform4fv(const char* name, float* data);

public:
	unsigned int getProgramID() { return glProgramID; }

private:
	GLuint glProgramID;
};