#include "TextureBufferCache.h"

TextureBufferCache::TextureBufferCache()
{

}

TextureBufferCache::~TextureBufferCache()
{
	_buffers.clear();
}

std::shared_ptr<TextureBuffer>TextureBufferCache::findOrCreate(std::string filename)
{
	auto iter = _buffers.find(filename);

	if (iter == _buffers.end())
	{
		auto buf = std::make_shared<TextureBuffer>(filename);
		_buffers.insert(std::pair<std::string, std::shared_ptr<TextureBuffer>>(filename, buf));

		return buf;
	}
	else
	{
		return iter->second;
	}
}