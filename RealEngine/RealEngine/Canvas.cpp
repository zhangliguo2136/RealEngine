#include "Canvas.h"
#include "Image2D.h"
//#include "GCObjectPool.h"

Canvas::Canvas()
{
	// ����ĳߴ����Ӱ�죬������2�Ĵη�
	//Image2D* image = GCObjectPool::NewObject<Image2D>(this);
	//image->LoadImageFormFile("../Resource/images/particle.png");

	//Image2D* image = new Image2D("../Resource/images/particle.png");
	//this->addChild(image);
}

Canvas::~Canvas()
{
}