#include "TextureGLCache.h"

TextureGLCache::TextureGLCache()
{

}

TextureGLCache::~TextureGLCache()
{
	_buffers.clear();
}

std::shared_ptr<TextureGL>TextureGLCache::findOrCreate(std::string filename)
{
	auto iter = _buffers.find(filename);

	if (iter == _buffers.end())
	{
		auto buf = std::make_shared<TextureGL>(filename);
		_buffers.insert(std::pair<std::string, std::shared_ptr<TextureGL>>(filename, buf));

		return buf;
	}
	else
	{
		return iter->second;
	}
}