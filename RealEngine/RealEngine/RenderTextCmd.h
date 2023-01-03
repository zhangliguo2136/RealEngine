#pragma once
#include "RenderCommand.h"
#include "Vector.h"
#include "TextureGL.h"
#include "Shader.h"

#include <map>
#include <string>


class RenderTextCmd :public RenderCommand
{
public:
	virtual void execute() override;

public:
	RenderTextCmd();
	~RenderTextCmd();

public:
	std::string content;

	std::map<unsigned char, std::shared_ptr<TextureGL>> glTextures;
	std::map<unsigned char, Vector2i> sizes;
	std::map<unsigned char, Vector2i> bearings;
	std::map<unsigned char, unsigned int> advances;

private:
	std::shared_ptr<Shader> _shader;
};