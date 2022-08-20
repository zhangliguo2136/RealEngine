#pragma once
#include "RenderCommand.h"
#include "Vector.h"
#include "Texture2D.h"

#include <map>
#include <string>


class RenderTextCmd :public RenderCommand
{
public:
	virtual void execute() override;
public:
	Vector2i position;
	Vector2i size;
	Vector2f scale;
	Vector2i rotate;

public:
	std::string content;

	std::map<unsigned char, unsigned int> textures;
	std::map<unsigned char, Vector2i> sizes;
	std::map<unsigned char, Vector2i> bearings;
	std::map<unsigned char, unsigned int> advances;
};