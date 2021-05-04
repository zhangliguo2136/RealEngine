#include "Image.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"

#include <iostream>

using namespace std;

Image::Image() 
{

}
Image::~Image() 
{
	stbi_image_free(m_pData);
}

void Image::loadFromFile(std::string filename)
{
	m_pData = stbi_load(filename.c_str(), &width, &height, &nrChannel, 0);
}