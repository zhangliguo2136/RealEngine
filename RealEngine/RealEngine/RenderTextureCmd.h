#pragma once
#include "RenderCommand.h"
#include "TextureGL.h"
class RenderTextureCmd :public RenderCommand
{
public:
	virtual void execute() override;

public:
	RenderTextureCmd();
	~RenderTextureCmd();

public:
	unsigned int glTextureID = -1;
};