#include "GLProgram.h"

#include "GLShaderLoader.h"

GLProgram::GLProgram()
{
	glProgramID = glCreateProgram();
}

GLProgram::~GLProgram()
{
	glDeleteProgram(glProgramID);
}

void GLProgram::AttachProgram(const std::string& source, GLShaderType sType)
{
	GLuint glShaderID;

	if (sType == GLShaderType::SHADER_VERTEX)
	{
		glShaderID = LoadGLShaderID(source.c_str(), GL_VERTEX_SHADER);
	}
	else if (sType == GLShaderType::SHADER_FRAGMENT)
	{
		glShaderID = LoadGLShaderID(source.c_str(), GL_FRAGMENT_SHADER);
	}
	else if (sType == GLShaderType::SHADER_GEOMETRY)
	{
		glShaderID = LoadGLShaderID(source.c_str(), GL_GEOMETRY_SHADER);
	}
	else if (sType == GLShaderType::SHADER_COMPUTE)
	{
		glShaderID = LoadGLShaderID(source.c_str(), GL_COMPUTE_SHADER);
	}
	else
	{
		printf("Warnning::GLProgram:: AttachProgram shaderType is invalid.\n");

		return;
	}

	glAttachShader(glProgramID, glShaderID);

	glDeleteShader(glShaderID);
}

void GLProgram::LinkProgram()
{
	glLinkProgram(glProgramID);
}

void GLProgram::UseProgram() const
{
	glUseProgram(glProgramID);
}

void GLProgram::Dispatch(int x, int y, int z)
{
	printf("Warnning::GLProgram::Dispatch() only ComputeShader can Dispatch\n");
}

void GLProgram::setUniformMatrix4fv(const char* name, float* data)
{
	GLuint loc = glGetUniformLocation(glProgramID, name);

	glUniformMatrix4fv(loc, 1, GL_FALSE, data);
}

void GLProgram::setUniform3fv(const char* name, float* data)
{
	GLuint loc = glGetUniformLocation(glProgramID, name);

	glUniform3fv(loc, 1, data);
}

void GLProgram::setUniform4fv(const char* name, float* data)
{
	GLuint loc = glGetUniformLocation(glProgramID, name);

	glUniform4fv(loc, 1, data);
}

void GLProgram::setUniform1i(const char* name, unsigned int i)
{
	GLuint loc = glGetUniformLocation(glProgramID, name);

	glUniform1i(loc, i);
}