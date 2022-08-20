#pragma once

#include "Node.h"
#include "Texture2D.h"

class Image2D :public Node
{
public:
	virtual void onDraw() override;

public:
	Image2D(std::string filename);
	~Image2D();

private:
	int width = 0;
	int height = 0;
	int nrChannel = 0;

public:
	std::string m_filename;

	unsigned char* m_pData = nullptr;

	Texture2D* m_Texture = nullptr;
};