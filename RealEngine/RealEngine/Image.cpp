#include "Image.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"

#include <iostream>

using namespace std;

Image::Image(std::string filename) 
{
	loadFromFile(filename);
}
Image::~Image() 
{
	stbi_image_free(m_pData);
}

void Image::loadFromFile(std::string filename)
{
	m_pData = stbi_load(filename.c_str(), &width, &height, &nrChannel, 0);
}

void Image::loadFromMemoryTest(std::string filename)
{
	FILE* inFile;
	fopen_s(&inFile, filename.c_str(), "rb");
	fseek(inFile, 0, SEEK_END);
	unsigned int bufSize = ftell(inFile);
	fseek(inFile, 0, SEEK_SET);

	unsigned char* buf = new unsigned char[bufSize];
	fread(buf, bufSize, 1, inFile);
	fclose(inFile);

	m_pData = stbi_load_from_memory(buf, bufSize, &width, &height, &nrChannel, 0);

	delete[] buf;
}