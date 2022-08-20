#pragma once

#include <map>
#include <vector>
#include <stdarg.h>

#include "Node.h"
#include "Vector.h"
#include "Texture2D.h"

static std::string format(const char *pszFmt, ...)
{
	std::string str;
	va_list args;
	va_start(args, pszFmt);
	{
		int nLength = _vscprintf(pszFmt, args);
		nLength += 1;  //上面返回的长度是包含\0，这里加上
		std::vector<char> chars(nLength);

		_vsnprintf_s(chars.data(), nLength, nLength, pszFmt, args);

		str.assign(chars.data());
	}
	va_end(args);
	return str;
}

struct Character
{
	Texture2D TextureID;
	Vector2i Size;
	Vector2i Bearing;
	unsigned int Advance;
};

class Text :public Node
{
public:
	Text();
	~Text();

	void onDraw();

private:
	//std::map<unsigned char, Character> _characters;
	std::map<unsigned char, unsigned int> _textures;
	std::map<unsigned char, Vector2i> _sizes;
	std::map<unsigned char, Vector2i> _bearings;
	std::map<unsigned char, unsigned int> _advances;
public:
	void setText(std::string inContent)
	{
		_content = inContent;
	};
	void setText(float inContent)
	{
		_content = format("%.2f", inContent);
	};


private:
	std::string _content;
};