#pragma once

#include <map>
#include <vector>

#include "Vector.h"
#include "Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stdarg.h>

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
	unsigned int Texture;
	Vector2i Size;
	Vector2i Bearing;
	unsigned int Advance;
};

class Text
{
public:
	Text();
	~Text();

	void draw();


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

	std::map<unsigned char, Character> _characters;

	unsigned int _vao;
	unsigned int _vbo;

	Shader* _shader = nullptr;
};