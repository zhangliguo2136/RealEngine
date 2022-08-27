#pragma once

#include "Vector.h"

class RenderCommand
{
public:
	virtual void execute();

public:
	Vector2i position;
	Vector2i size;
	Vector2f scale;
	Vector2i rotate;
};