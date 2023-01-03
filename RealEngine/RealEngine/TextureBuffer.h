#pragma once
#include <iostream>

class TextureBuffer
{
public:
	TextureBuffer() {};
	~TextureBuffer();

	TextureBuffer(std::string filename);

	unsigned char At(int idx)
	{
		if (idx < 0 || idx >= bufWidth * bufHeight * bufChannel)
		{
			printf("TextureBuffer::At {%d} Out of Range!", idx);
		}

		return buf[idx];
	}


	int GetWidth()
	{
		return bufWidth;
	};
	int GetHeight()
	{
		return bufHeight;
	};

	int GetChannel()
	{
		return bufChannel;
	};

	unsigned char* GetBuffer()
	{
		return buf;
	}

private:
	unsigned char* buf = nullptr;

	int bufWidth = 0;
	int bufHeight = 0;
	int bufChannel = 0;
};