#pragma once
#include <map>
#include <vector>
#include <memory>

#include "TextureGL.h"

class TextureGLCache
{
public:
	TextureGLCache();
	~TextureGLCache();

	static TextureGLCache& getInstance()
	{
		static TextureGLCache instance;
		return instance;
	}

	TextureGLCache(const TextureGLCache&) = delete;
	TextureGLCache& operator = (const TextureGLCache&) = delete;

public:
	std::shared_ptr<TextureGL> findOrCreate(std::string filename);

private:
	std::map<std::string, std::shared_ptr<TextureGL>> _buffers;
};