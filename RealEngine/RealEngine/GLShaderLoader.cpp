#include "GLShaderLoader.h"

GLuint LoadGLShaderID(const GLchar *source, GLenum shaderType)
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

		printf("Warnning::Unable to load a shader : %s", std::string(infoLog).c_str());
	}

	return shaderID;
}
