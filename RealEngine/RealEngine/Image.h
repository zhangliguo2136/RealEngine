#pragma once
#include <string>

class Image 
{
public:
	Image(std::string filename);
	~Image();

	void loadFromFile(std::string filename);
private:
	int height;
	int width;
	int nrChannel;

	unsigned char* m_pData;

	unsigned int mTextureID;
	void loadTexture();
	void unloadTexture();

	void bindVertexArray();
private:
	void loadFromMemoryTest(std::string filename);
public:
	void draw();
};