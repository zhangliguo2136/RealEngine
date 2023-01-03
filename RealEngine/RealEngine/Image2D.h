#pragma once

#include "Node.h"
#include "TextureGL.h"

class Image2D :public Node
{
public:
	virtual void onDraw() override;

public:
	Image2D() {};
	Image2D(std::string filename);
	~Image2D();

public:
	void LoadImageFormFile(std::string filename);

public:
	std::string m_filename;

public:
	TextureGL* glTexture = nullptr;
};