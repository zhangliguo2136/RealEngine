#include "Text.h"

#include <ft2build.h>
#include FT_FREETYPE_H

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

Text::Text():_content("")
{
	FT_Library ft;
	if (FT_Init_FreeType(&ft))
	{
		printf("ERROR::FREETYPE: Could not init FreeType Library");
	}

	FT_Face face;
	if (FT_New_Face(ft, "../resource/fonts/arial.ttf", 0, &face))
	{
		printf("ERROR::FREETYPE: Failed to load font");
	}
	
	FT_Set_Pixel_Sizes(face, 0, 48);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	for (unsigned char c = 0; c < 128; c++)
	{
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			printf("ERROR::FREETYTPE: Failed to load Glyph");
			continue;
		}

		unsigned int texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED, 
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer
		);

		// 设置纹理选项
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		Character character =
		{
			texture,
			Vector2i(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			Vector2i(face->glyph->bitmap_left, face->glyph->bitmap_top),
			face->glyph->advance.x
		};

		_characters.insert(std::pair<unsigned char, Character>(c, character));
	}
	glBindTexture(GL_TEXTURE_2D, 0);

	FT_Done_Face(face);
	FT_Done_FreeType(ft);

	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	glGenBuffers(1, &_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	_shader = new Shader("../Resource/shaders/Text.vs", "../Resource/shaders/Text.fs");
}

Text::~Text()
{

}

void Text::draw()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glm::mat4 projection = glm::ortho(0.0f, 1920.f, 0.0f, 1080.f);

	Vector3f color = Vector3f(1.0, 1.0, 1.0);
	float x = 0.f;
	float y = 0.f;
	float scale = 1.0f;

	_shader->useProgram();
	_shader->setUniformMatrix4fv("projection", glm::value_ptr(projection));
	_shader->setUniform3fv("color", color.values);

	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(_vao);

	for (auto c = _content.begin(); c < _content.end(); c++)
	{
		Character ch = _characters[*c];

		GLfloat xpos = x + ch.Bearing.x * scale;
		GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

		GLfloat w = ch.Size.x * scale;
		GLfloat h = ch.Size.y * scale;
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
		glBindTexture(GL_TEXTURE_2D, ch.Texture);
		// 更新VBO内存的内容
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// 绘制四边形
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// 更新位置到下一个字形的原点，注意单位是1/64像素
		x += (ch.Advance >> 6) * scale; // 位偏移6个单位来获取单位为像素的值 (2^6 = 64)
	}

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}