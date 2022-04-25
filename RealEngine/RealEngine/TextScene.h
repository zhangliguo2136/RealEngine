#pragma once

#include "Text.h"

class TextScene
{
public:
	TextScene();
	~TextScene();

	void update(float deltaTime);

private:
	Text* _myText = nullptr;
};