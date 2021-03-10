#include "Shader.h"
#include "ShaderLoader.h"

Shader::Shader(const std::string &vertexFile, const std::string &fragmentFile)
	:m_id(loadShaders(vertexFile, fragmentFile))
{
	useProgram;
}

Shader::~Shader() 
{
	glDeleteProgram(m_id);
}

void Shader::useProgram() const
{
	glUseProgram(m_id);
}