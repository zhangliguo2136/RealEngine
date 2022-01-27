#include "ComputeShader.h"
#include "FileUtil.h"

ComputeShader::ComputeShader(std::string filename) 
{
	std::string sourceFile = getFileContents(filename);
	const char* source = sourceFile.c_str();

	GLuint shaderID = glCreateShader(GL_COMPUTE_SHADER);

	glShaderSource(shaderID, 1, &source, nullptr);
	glCompileShader(shaderID);

	GLint isSuccess = 0;
	GLchar infoLog[512];

	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &isSuccess);

	if (!isSuccess)
	{
		glGetShaderInfoLog(shaderID, 512, nullptr, infoLog);
		throw std::runtime_error("Unable to load a compute shader:" + std::string(infoLog));
	}

	m_id = glCreateProgram();
	glAttachShader(m_id, shaderID);
	glLinkProgram(m_id);

	glDeleteShader(shaderID);
}
ComputeShader::~ComputeShader() 
{
	glDeleteProgram(m_id);
}

void ComputeShader::UseProgram()
{
	glUseProgram(m_id);
}

void ComputeShader::Dispatch(int x, int y, int z)
{
	glDispatchCompute(x, y, z);
}