#include "TextureBuffer.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"

TextureBuffer::~TextureBuffer()
{
	free(buf);
	buf = nullptr;
}

TextureBuffer::TextureBuffer(std::string filename)
{
	unsigned char* pData = stbi_load(filename.c_str(), &bufWidth, &bufHeight, &bufChannel, 0);

	if (!pData)
	{
		printf("TextureBuffer::failed to load at file: %s\n", filename.c_str());
		return;
	}

	buf = (unsigned char*)malloc(bufWidth * bufHeight * bufChannel);
	memcpy(buf, pData, bufWidth * bufHeight * bufChannel);
	stbi_image_free(pData);
}