#pragma once
#include <iostream>

#include "TextureBuffer.h"

class ObjMatrial
{
public:
	ObjMatrial();
	~ObjMatrial();

public:
	// 材质名称
	std::string _name;

	// 暂时只需要漫反射纹理
	TextureBuffer* diffuseTexture = nullptr;
};