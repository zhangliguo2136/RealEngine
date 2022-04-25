#include "TextScene.h"

TextScene::TextScene()
{
	_myText = new Text();
	_myText->setText("Hello World");
}

TextScene::~TextScene()
{

}

void TextScene::update(float deltaTime)
{
	_myText->draw();
}