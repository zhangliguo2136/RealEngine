#pragma once
#include <string>

// 当前录入的关键字
char token[32] = { '\0' };

int index = 0;

//关键字列表
char keys[5][32] = { "if", "else", "for", "while", "break" };
char typeKeys[4][16] = { "TValue", "TFunction", "TClass", "TObject" };

bool isChar(char tmp)
{
	if (tmp >= 'a'&& tmp <= 'z')
	{
		return true;
	}
	if (tmp >= 'A'&& tmp <= 'Z')
	{
		return true;
	}
	return false;
}

bool isNormalKey(char key[32])
{
	for (int i = 0; i < 5; i++)
	{
		if (strcmp(keys[i], key) == 0)
		{
			return true;
		}
	}
	return false;
}

bool isTypeKey(char key[32])
{
	for (int i = 0; i < 4; i++)
	{
		if (strcmp(typeKeys[i], key) == 0)
		{
			return true;
		}
	}
	return false;
}

void scanner(std::string contents)
{
	if (contents[index] == ' ')
	{
		index++;
	}

	if (isChar(contents[index]))
	{
		int count = 0;
		while (isChar(contents[index]))
		{
			token[count] = contents[index];
			count++;
		}
		token[count] = '\0';

		if (isNormalKey(token))
		{
			// TODO 如果是关键字
		}
		if (isTypeKey(token))
		{
			// 如果是类型关键字
		}
	}
}

void parser(std::string contents)
{
	while (true)
	{
		scanner(contents);
	}
}