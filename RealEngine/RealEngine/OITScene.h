#pragma once

#include "Shader.h"

/*
透明度顺序无关算法
*/
class OITScene
{
public:
	OITScene();
	~OITScene();

	void update(float deltaTime);

private:
	Shader* _buildShader = nullptr;
	Shader* _resolveShader = nullptr;

	unsigned int head_pointer_texture;
	unsigned int head_pointer_clear_buffer;
	unsigned int atomic_counter_buffer;
	unsigned int linked_list_buffer;
	unsigned int linked_list_texture;

	unsigned int vao;
};