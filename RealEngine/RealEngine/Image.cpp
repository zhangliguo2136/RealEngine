#include "Image.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"

#include <iostream>
#include "Shader.h"

using namespace std;

Image::Image(std::string filename) 
{
	loadFromFile(filename);
}
Image::~Image() 
{
	stbi_image_free(m_pData);
}

void Image::loadFromFile(std::string filename)
{
	m_pData = stbi_load(filename.c_str(), &width, &height, &nrChannel, 0);
}

void Image::loadFromMemoryTest(std::string filename)
{
	FILE* inFile;
	fopen_s(&inFile, filename.c_str(), "rb");
	fseek(inFile, 0, SEEK_END);
	unsigned int bufSize = ftell(inFile);
	fseek(inFile, 0, SEEK_SET);

	unsigned char* buf = new unsigned char[bufSize];
	fread(buf, bufSize, 1, inFile);
	fclose(inFile);

	m_pData = stbi_load_from_memory(buf, bufSize, &width, &height, &nrChannel, 0);

	delete[] buf;
}

void Image::draw()
{
	glClearColor(0.86f, 0.86f, 0.86f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	Shader* shader = new Shader("../Resource/shader/common.vert", "../Resource/shader/common.frag");
	shader->setActive();

	/*-------------------------------------------------*/
	// 顶点
	float vertexBuffer[] = 
	{
		-0.5f,	0.5f, 0.0f,
		0.5f,	0.5f, 0.0f,
		0.5f,  -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f
	};
	// 顶点索引
	unsigned int indexBuffer[] = 
	{
		0, 1, 2,
		2, 3, 0
	};
	// 创建顶点数组对象
	unsigned int vao, vbo, ebo;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// 顶点缓冲对象
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBuffer), vertexBuffer, GL_STATIC_DRAW);

	// 索引缓冲对象
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexBuffer), indexBuffer, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

	glBindVertexArray(vao);
	/*-------------------------------------------------*/

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

	delete shader;
}