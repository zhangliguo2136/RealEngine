#include "ShaderLoader.h"
#include "FileUtil.h"

namespace 
{
	GLuint compileShader(const GLchar *source, GLenum shaderType)
	{
		GLuint shaderID = glCreateShader(shaderType);

		glShaderSource(shaderID, 1, &source, nullptr);
		glCompileShader(shaderID);

		GLint isSuccess = 0;
		GLchar infoLog[512];

		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &isSuccess);

		if (!isSuccess) 
		{
			glGetShaderInfoLog(shaderID, 512, nullptr, infoLog);

			throw std::runtime_error("Unable to load a shader:" + std::string(infoLog));
		}

		return shaderID;
	}

	GLuint linkProgram(GLuint vertexShaderID, GLuint fragmentShaderID)
	{
		GLuint id = glCreateProgram();

		glAttachShader(id, vertexShaderID);
		glAttachShader(id, fragmentShaderID);

		glLinkProgram(id);

		return id;
	}
}

GLuint loadShaders(const std::string &vertexShader,
	const std::string &fragmentShader)
{
	std::string vertexSource = getFileContents(vertexShader);
	std::string fragmentSource = getFileContents(fragmentShader);

	GLuint vertexShaderID = compileShader(vertexSource.c_str(), GL_VERTEX_SHADER);
	GLuint fragmentShaderID = compileShader(fragmentSource.c_str(), GL_FRAGMENT_SHADER);

	GLuint shaderID = linkProgram(vertexShaderID, fragmentShaderID);

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	return shaderID;
}