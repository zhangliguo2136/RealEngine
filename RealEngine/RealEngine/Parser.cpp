#include "Parser.h"

// ��ǰ¼��Ĺؼ���
char token[32] = { '\0' };

int index = 0;

//�ؼ����б�
char keys[5][32] = { "if", "else", "for", "while", "break" };
char typeKeys[4][32] = { "TValue", "TFunction", "TClass", "TObject" };

// �ı��Ƿ����
bool isBreak = false;

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

	if (contents[index] == '\0')
	{
		isBreak = true;
	}

	if (isChar(contents[index]))
	{
		int count = 0;
		while (isChar(contents[index + count]))
		{
			token[count] = contents[index + count];
			count++;
		}
		index = index + count;
		token[count] = '\0';

		if (isNormalKey(token))
		{
			RealEngine::log("Script::Parser:: the normal key is %s\n", token);
			// TODO ����ǹؼ���

			memset(token, 0, sizeof(token));
		}
		if (isTypeKey(token))
		{
			RealEngine::log("Script::Parser:: the type key is %s\n", token);
			// ��������͹ؼ���

			memset(token, 0, sizeof(token));
		}
	}
}

void parser(std::string contents)
{
	while (true)
	{
		scanner(contents);

		if (isBreak)
		{
			break;
		}
	}
}