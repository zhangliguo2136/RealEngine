#include "UIScene.h"
#include "Image2D.h"

UIScene::UIScene()
{
	// ����ĳߴ����Ӱ�죬������2�Ĵη�
	Image2D* image = new Image2D("../Resource/images/particle.png");

	this->addChild(image);
}

UIScene::~UIScene()
{
}