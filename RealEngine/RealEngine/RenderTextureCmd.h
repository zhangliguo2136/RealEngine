#pragma once
#include "RenderCommand.h"
#include "TextureGL.h"
#include "Shader.h"

class RenderTextureCmd :public RenderCommand
{
public:
	virtual void execute() override;

public:
	RenderTextureCmd();
	~RenderTextureCmd();

public:

	std::shared_ptr<Shader> _shader;

	unsigned int glTextureID = -1;
};