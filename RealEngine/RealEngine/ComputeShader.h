#pragma once
#include <string>

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

class ComputeShader
{
public:
	ComputeShader(std::string filename);
	~ComputeShader();

	void UseProgram();
	void Dispatch(int x = 1, int y = 1, int z = 1);

private:
	unsigned int m_id;
};