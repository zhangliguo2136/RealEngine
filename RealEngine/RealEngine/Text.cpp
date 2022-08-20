#include "Text.h"

#include <ft2build.h>
#include FT_FREETYPE_H

#include "RenderSystem.h"
#include "RenderTextCmd.h"

#include <memory>

Text::Text() :_content("")
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
	
	for (unsigned char c = 0; c < 128; c++)
	{
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			printf("ERROR::FREETYTPE: Failed to load Glyph");
			continue;
		}

		Texture2D texture2D = Texture2D(face->glyph->bitmap.buffer, face->glyph->bitmap.width, face->glyph->bitmap.rows, 1);

		_textures.insert(std::pair<unsigned char, unsigned int>(c, texture2D.getTextureID()));
		_sizes.insert(std::pair<unsigned char, Vector2i>(c, Vector2i(face->glyph->bitmap.width, face->glyph->bitmap.rows)));
		_bearings.insert(std::pair<unsigned char, Vector2i>(c, Vector2i(face->glyph->bitmap_left, face->glyph->bitmap_top)));
		_advances.insert(std::pair<unsigned char, unsigned int>(c, face->glyph->advance.x));
	}

	FT_Done_Face(face);
	FT_Done_FreeType(ft);
}

Text::~Text()
{

}

void Text::onDraw()
{
	std::shared_ptr<RenderTextCmd> cmd = std::make_shared<RenderTextCmd>();
	cmd->position = this->getPosition();
	cmd->size = this->getSize();
	cmd->rotate = this->getRotation();
	cmd->scale = this->getScale();

	cmd->content = _content;
	cmd->textures = _textures;
	cmd->sizes = _sizes;
	cmd->bearings = _bearings;
	cmd->advances = _advances;

	auto& renderSys = RenderSystem::getInstance();
	renderSys.AddCommand(cmd);
}