#include "RenderTextureCmd.h"
#include "Matrix.h"
#include "ShaderCache.h"

void RenderTextureCmd::execute()
{
	// 顶点
	float vertexBuffer[] =
	{
		-1.f,	1.f,  0.0f, 0.0f, 0.0f,
		1.0f,	1.f,  0.0f, 1.0f, 0.0f,
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
	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	{
		// 顶点缓冲对象
		unsigned int vbo;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBuffer), vertexBuffer, GL_STATIC_DRAW);

		// 索引缓冲对象
		unsigned int ebo;
		glGenBuffers(1, &ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexBuffer), indexBuffer, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)0);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(3 * sizeof(float)));

	}
	glBindVertexArray(0);

	{
		_shader->useProgram();

		Matrix4 view = Matrix4::IdentityMatrix();
		Matrix4 projection = Matrix4::IdentityMatrix();

		_shader->setUniformMatrix4fv("uWorldTransform", projection.data());
		_shader->setUniformMatrix4fv("uViewProj", view.data());
	}

	//draw
	glBindTexture(GL_TEXTURE_2D, m_Texture->getTextureID());
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}


RenderTextureCmd::RenderTextureCmd()
{
	auto& shaderCache = ShaderCache::getInstance();
	_shader = shaderCache.findOrCreate("Sprite");
}

RenderTextureCmd::~RenderTextureCmd()
{
	m_Texture = nullptr;
	_shader = nullptr;
}