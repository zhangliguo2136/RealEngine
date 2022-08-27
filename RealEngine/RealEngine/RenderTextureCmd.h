#pragma once
#include "RenderCommand.h"
#include "Texture2D.h"
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
	Texture2D* m_Texture = nullptr;
};