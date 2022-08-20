#pragma once

class Texture2D
{
public:
	Texture2D();
	~Texture2D();

	Texture2D(unsigned char* pData, int width, int height, int nrChannel);

	unsigned int getTextureID() { return m_TextureID; };

private:
	unsigned int m_TextureID = -1;
};