#pragma once
#include <iostream>

#include "TextureBuffer.h"

class ObjMatrial
{
public:
	ObjMatrial();
	~ObjMatrial();

public:
	// ��������
	std::string _name;

	// ��ʱֻ��Ҫ����������
	TextureBuffer* diffuseTexture = nullptr;
};