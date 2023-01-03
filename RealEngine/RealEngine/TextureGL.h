#pragma once

#include <iostream>

class TextureGL
{
public:
	TextureGL() {};
	~TextureGL();

	TextureGL(unsigned char* pData, int width, int height, int nrChannel);
	TextureGL(std::string filename);

	unsigned int getTextureID() { return m_TextureID; };

private:
	unsigned int m_TextureID = -1;
};