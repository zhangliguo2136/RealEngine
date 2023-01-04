#include "OITScene.h"

#include <string>

#include "Vector.h"
#include "GLShaderCache.h"

OITScene::OITScene()
{
	// 头指针纹理
	//unsigned int head_pointer_texture;
	glGenTextures(1, &head_pointer_texture);
	glBindTexture(GL_TEXTURE_2D, head_pointer_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_R32UI, 2048, 2048, 0, GL_RED_INTEGER, GL_UNSIGNED_INT, NULL);
	glBindTexture(GL_TEXTURE_2D, 0);

	glBindImageTexture(0, head_pointer_texture, 0, GL_TRUE, 0, GL_READ_WRITE, GL_R32UI);

	// CLEAR 头指针纹理 的 缓冲（每一帧开始的前清理）
	//unsigned int head_pointer_clear_buffer;
	glGenBuffers(1, &head_pointer_clear_buffer);
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER, head_pointer_clear_buffer);
	glBufferData(GL_PIXEL_UNPACK_BUFFER, 2048 * 2048 * sizeof(unsigned int), NULL, GL_STATIC_DRAW);

	// 设置缓冲值
	void* buffer = glMapBuffer(GL_PIXEL_UNPACK_BUFFER, GL_WRITE_ONLY);
	memset(buffer, 0x00, 2048 * 2048 * sizeof(unsigned int));
	glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER);

	//创建原子计数器缓冲
	//unsigned int atomic_counter_buffer;
	glGenBuffers(1, &atomic_counter_buffer);
	glBindBuffer(GL_ATOMIC_COUNTER_BUFFER, atomic_counter_buffer);
	glBufferData(GL_ATOMIC_COUNTER_BUFFER, sizeof(unsigned int), NULL, GL_DYNAMIC_COPY);

	// 创建一维缓冲（片段链表）
	//unsigned int linked_list_buffer;
	glGenBuffers(1, &linked_list_buffer);
	glBindBuffer(GL_TEXTURE_BUFFER, linked_list_buffer);
	glBufferData(GL_TEXTURE_BUFFER, 2048 * 2048 * 2 * sizeof(Vector3f), NULL, GL_DYNAMIC_COPY);
	glBindBuffer(GL_TEXTURE_BUFFER, 0);

	// 创建纹理
	//unsigned int linked_list_texture;
	glGenTextures(1, &linked_list_texture);
	glBindTexture(GL_TEXTURE_BUFFER, linked_list_texture);
	glTexBuffer(GL_TEXTURE_BUFFER, GL_RGBA32UI, linked_list_buffer);
	glBindTexture(GL_TEXTURE_BUFFER, 0);

	

	// 创建vao
	//unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	static const GLfloat quad_verts[] =
	{
		-0.0f, -1.0f,
		 1.0f, -1.0f,
		-0.0f,  1.0f,
		 1.0f,  1.0f,
	};

	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quad_verts), quad_verts,  GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);

	auto& shaderCache = GLShaderCache::getInstance();
	_buildShader = shaderCache.findOrCreate("oit_build_list");
	_resolveShader = shaderCache.findOrCreate("oit_resolve");
}

OITScene::~OITScene() 
{

}

void OITScene::update(float deltaTime)
{
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// 重置原子计数器
	glBindBufferBase(GL_ATOMIC_COUNTER_BUFFER, 0, atomic_counter_buffer);

	unsigned int* buffer = (unsigned int*)glMapBuffer(GL_ATOMIC_COUNTER_BUFFER, GL_WRITE_ONLY);
	buffer[0] = 0;
	glUnmapBuffer(GL_ATOMIC_COUNTER_BUFFER);

	// 重置头指针纹理
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER, head_pointer_texture);
	glBindTexture(GL_TEXTURE_2D, head_pointer_texture);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 1920, 1080, GL_RED_INTEGER, GL_UNSIGNED_INT, NULL);
	glBindTexture(GL_TEXTURE_2D, 0);

	glBindImageTexture(0, head_pointer_texture, 0, GL_FALSE, 0, GL_READ_WRITE, GL_R32UI);

	glBindImageTexture(1, linked_list_texture, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32UI);

	/*-----------------------------------------------*/
	_buildShader->UseProgram();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// DRAW OBJ
	//.......

	glDisable(GL_BLEND);
	/*-----------------------------------------------*/


	_resolveShader->UseProgram();
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	/*-----------------------------------------------*/
}