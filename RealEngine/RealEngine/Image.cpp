#include "Image.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"

#include <iostream>
#include "Shader.h"
#include "Quaternion.h"
#include "SceneManager.h"
#include "Vector.h"
#include "Math.h"

using namespace std;

Image::Image(std::string filename) 
{
	_model.Identity();

	loadFromFile(filename);
}
Image::~Image() 
{
	stbi_image_free(m_pData);
}

void Image::loadFromFile(std::string filename)
{
	m_pData = stbi_load(filename.c_str(), &width, &height, &nrChannel, 0);

	RealEngine::SceneManager& pManager = RealEngine::SceneManager::getInstance();
	Size winSize = pManager.getWinSize();
	float scaleX = width / winSize.width;
	float scaleY = height / winSize.height;
	SetScale(scaleX, scaleX, 1.f);
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

unsigned int Image::BindTexture(std::string filename)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	else
	{
		printf("Texture failed to load at file: %s", filename.c_str());
	}
	stbi_image_free(data);
	return textureID;
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

	//glBindVertexArray(0);
}

void Image::draw()
{

	glClearColor(0.86f, 0.86f, 0.86f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	Shader* shader = new Shader("../Resource/shader/sprite.vert", "../Resource/shader/sprite.frag");
	shader->useProgram();

	RealEngine::SceneManager& pManager = RealEngine::SceneManager::getInstance();
	Size winSize = pManager.getWinSize();

	//SetPosition(winSize.width/2, winSize.height/2, 0.f);
	//SetRotation(180.f);

	//shader->setMatrixUniform("uWorldTransform", uWorldTransform);

	//Matrix4 projMat4;
	//projMat4.Identity();
	//shader->setMatrixUniform("uViewProj", &projMat4);

	bindVertexArray();
	loadTexture();

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

	unloadTexture();
	delete shader;
}

void Image::SetPosition(float inx, float iny, float inz) 
{
	RealEngine::SceneManager& pManager = RealEngine::SceneManager::getInstance();
	Size winSize = pManager.getWinSize();

	float x = inx / winSize.width - 0.5f;
	float y = iny / winSize.height - 0.5f;

	Matrix4 transfrom = Matrix4::Translate(Vector3f(x, y, 0.0f));
	_model = _model * transfrom;
}
void Image::SetScale(float scaleX, float scaleY, float scaleZ) 
{
	Matrix4 transfrom = Matrix4::Scale(Vector3f(scaleX - 1.f, scaleY - 1.f, scaleZ - 1.f));
	_model = _model * transfrom;
}
void Image::SetRotation(float angle) 
{
	Quaternion quat(Vector3f(0.0f, 0.0f, 1.0f), Math::radians(angle));
	Matrix4 rotation = Matrix4::RotationByQuat(quat);

	_model = _model * rotation;
}