#pragma once
#include <map>
#include <vector>
#include <memory>

#include "TextureBuffer.h"

class TextureBufferCache
{
public:
	TextureBufferCache();
	~TextureBufferCache();

	static TextureBufferCache& getInstance()
	{
		static TextureBufferCache instance;
		return instance;
	}

	TextureBufferCache(const TextureBufferCache&) = delete;
	TextureBufferCache& operator = (const TextureBufferCache&) = delete;

public:
	std::shared_ptr<TextureBuffer> findOrCreate(std::string filename);

private:
	std::map<std::string, std::shared_ptr<TextureBuffer>> _buffers;
};