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

			printf("Unable to load a shader : %s", std::string(infoLog).c_str());
		}

		return shaderID;
	}

	GLuint linkProgram(GLuint vertexShaderID, GLuint fragmentShaderID, GLuint geomShaderID = 0)
	{
		GLuint id = glCreateProgram();

		glAttachShader(id, vertexShaderID);
		glAttachShader(id, fragmentShaderID);

		if (geomShaderID > 0) { glAttachShader(id, geomShaderID); }

		glLinkProgram(id);

		return id;
	}
}

GLuint loadShaders(const std::string &vertexShader,
	const std::string &fragmentShader, const std::string &geomShader)
{
	std::string vertexSource = getFileContents(vertexShader);
	printf("%s\n", vertexShader.c_str());

	std::string fragmentSource = getFileContents(fragmentShader);
	printf("%s\n", fragmentShader.c_str());

	GLuint vertexShaderID = compileShader(vertexSource.c_str(), GL_VERTEX_SHADER);
	GLuint fragmentShaderID = compileShader(fragmentSource.c_str(), GL_FRAGMENT_SHADER);

	GLuint gemonShaderID = 0;
	if (!geomShader.empty())
	{
		std::string geomSource = getFileContents(geomShader);
		printf("%s\n", geomShader.c_str());
		gemonShaderID = compileShader(geomSource.c_str(), GL_GEOMETRY_SHADER);
	}

	GLuint shaderID = linkProgram(vertexShaderID, fragmentShaderID, gemonShaderID);

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	if (gemonShaderID > 0) { glDeleteShader(gemonShaderID); }

	return shaderID;
}