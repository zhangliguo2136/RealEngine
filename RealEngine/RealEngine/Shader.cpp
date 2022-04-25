#include "Shader.h"
#include "ShaderLoader.h"

Shader::Shader(const std::string &vertexFile, const std::string &fragmentFile, const std::string &geomFile)
{
	m_id = loadShaders(vertexFile, fragmentFile, geomFile);
}

Shader::~Shader() 
{
	glDeleteProgram(m_id);
}

void Shader::useProgram() const
{
	glUseProgram(m_id);
}

void Shader::setUniformMatrix4fv(const char* name, float* data)
{
	GLuint loc = glGetUniformLocation(m_id, name);

	glUniformMatrix4fv(loc, 1, GL_FALSE, data);
}

void Shader::setUniform3fv(const char* name, float* data)
{
	GLuint loc = glGetUniformLocation(m_id, name);

	glUniform3fv(loc, 1, data);
}

void Shader::setUniform4fv(const char* name, float* data)
{
	GLuint loc = glGetUniformLocation(m_id, name);

	glUniform4fv(loc, 1, data);
}

void Shader::setUniform1i(const char* name, unsigned int i)
{
	GLuint loc = glGetUniformLocation(m_id, name);

	glUniform1i(loc, i);
}
