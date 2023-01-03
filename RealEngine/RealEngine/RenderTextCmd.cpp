#include "RenderTextCmd.h"
#include "Shader.h"
#include "ShaderCache.h"

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void RenderTextCmd::execute()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	unsigned int _vao;
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	unsigned int _vbo;
	glGenBuffers(1, &_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	{
		glm::mat4 projection = glm::ortho(0.0f, 1920.f, 0.0f, 1080.f);
		Vector3f color = Vector3f(1.0, 1.0, 1.0);

		_shader->useProgram();
		_shader->setUniformMatrix4fv("projection", glm::value_ptr(projection));
		_shader->setUniform3fv("color", color.values);
	}

	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(_vao);


	float x = position.x;
	float y = position.y;
	
	for (auto c = content.begin(); c < content.end(); c++)
	{
		std::shared_ptr<TextureGL> texture = glTextures[*c];
		Vector2i size = sizes[*c];
		Vector2i bearing = bearings[*c];
		unsigned int advance = advances[*c];

		GLfloat xpos = x + bearing.x * scale.x;
		GLfloat ypos = y - (size.y - bearing.y) * scale.y;

		GLfloat w = size.x * scale.x;
		GLfloat h = size.y * scale.y;
		// 对每个字符更新VBO
		GLfloat vertices[6][4] = {
			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos,     ypos,       0.0, 1.0 },
			{ xpos + w, ypos,       1.0, 1.0 },

			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos + w, ypos,       1.0, 1.0 },
			{ xpos + w, ypos + h,   1.0, 0.0 }
		};

		// 在四边形上绘制字形纹理
		glBindTexture(GL_TEXTURE_2D, texture->getTextureID());
		// 更新VBO内存的内容
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// 绘制四边形
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// 更新位置到下一个字形的原点，注意单位是1/64像素
		x += (advance >> 6) * scale.x; // 位偏移6个单位来获取单位为像素的值 (2^6 = 64)
	}

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

RenderTextCmd::RenderTextCmd()
{
	auto& shaderCache = ShaderCache::getInstance();
	_shader = shaderCache.findOrCreate("Text");
}

RenderTextCmd::~RenderTextCmd() 
{
	_shader = nullptr;
}