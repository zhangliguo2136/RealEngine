#pragma once
#include "RenderCommand.h"
#include "Vector.h"
#include "Texture2D.h"

class RenderTextureCmd :public RenderCommand
{
public:
	virtual void execute() override;

public:
	Vector2i position;
	Vector2i size;
	Vector2i rotate;
	Vector2f scale;

public:
	Texture2D* texture = nullptr;
};