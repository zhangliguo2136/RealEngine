#include "UIScene.h"
#include "Image2D.h"
//#include "GCObjectPool.h"

UIScene::UIScene()
{
	// 纹理的尺寸会有影响，尽量用2的次方
	//Image2D* image = GCObjectPool::NewObject<Image2D>(this);
	//image->loadImageFormFile("../Resource/images/particle.png");
	Image2D* image = new Image2D("../Resource/images/particle.png");

	this->addChild(image);
}

UIScene::~UIScene()
{
}