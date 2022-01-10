#include "Shader.h"
#include "ShaderLoader.h"

Shader::Shader(const std::string &vertexFile, const std::string &fragmentFile)
{
	m_id = loadShaders(vertexFile, fragmentFile);
}

Shader::~Shader() 
{
	glDeleteProgram(m_id);
}

void Shader::useProgram() const
{
	glUseProgram(m_id);
}

void Shader::setMatrixUniform(const char* name, float* data)
{
	GLuint loc = glGetUniformLocation(m_id, name);

	glUniformMatrix4fv(loc, 1, GL_FALSE, data);
}

void Shader::setUniform1i(const char* name, unsigned int i)
{
	GLuint loc = glGetUniformLocation(m_id, name);

	glUniform1i(loc, i);
}
