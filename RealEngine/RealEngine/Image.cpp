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

void Image::loadTexture()
{
	// rgb 格式 一个像素三个字节 所以重设对齐方式， 默认是4字节对齐
	// glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glGenTextures(1, &mTextureID);
	glBindTexture(GL_TEXTURE_2D, mTextureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_pData);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, mTextureID);
}
void Image::unloadTexture()
{
	glDeleteTextures(1, &mTextureID);

	mTextureID = -1;
}

void Image::bindVertexArray()
{
	/*-------------------------------------------------*/
// 顶点
	float vertexBuffer[] =
	{
		-1.f,	1.f, 0.0f, 0.0f, 0.0f,
		1.0f,	1.f, 0.0f, 1.0f, 0.0f,
		1.0f,  -1.0f, 0.0f, 1.0f, 1.0f,
		-1.f,  -1.0f, 0.0f, 0.0f, 1.0f
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, reinterpret_cast<void*>(sizeof(float) * 3));

	glBindVertexArray(vao);
}

void Image::draw()
{

	glClearColor(0.86f, 0.86f, 0.86f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	Shader* shader = new Shader("../Resource/shader/sprite.vert", "../Resource/shader/sprite.frag");
	shader->useProgram();

	Matrix4 tranform;
	tranform.Identity();
	tranform.MoveMatrix(Vector3f(0.0f, 0.0f, 0.0f));
	tranform.ScaleMatrix(Vector3f(-(1.0 - width/800.0), -(1.0 - height/600.0), 0.f));
	shader->setMatrixUniform("uWorldTransform", &tranform);

	Matrix4 projMat4;
	projMat4.Identity();
	shader->setMatrixUniform("uViewProj", &projMat4);

	bindVertexArray();
	loadTexture();

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

	unloadTexture();
	delete shader;
}