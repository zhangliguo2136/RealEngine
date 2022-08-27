#pragma once
#include "RenderCommand.h"
#include "Vector.h"
#include "Texture2D.h"
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

	std::map<unsigned char, std::shared_ptr<Texture2D>> textures;
	std::map<unsigned char, Vector2i> sizes;
	std::map<unsigned char, Vector2i> bearings;
	std::map<unsigned char, unsigned int> advances;

private:
	std::shared_ptr<Shader> _shader;
};