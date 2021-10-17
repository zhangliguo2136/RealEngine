#include "Parser.h"
#include <vector>

Parser::Parser()
{
	m_lineCount = 1;
}

bool Parser::isChar(const char& tmp)
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

bool Parser::isDight(const char& tmp)
{
	if (tmp >= '0'&& tmp <= '9')
	{
		return true;
	}
	return false;
}

bool Parser::isKeys(const char token[32])
{
	for (int i = 0; i < 4; i++)
	{
		if (strcmp(KEYS[i], token))
		{
			return true;
		}
	}
	return false;
}
bool Parser::isType(const char token[32])
{
	for (int i = 0; i < 4; i++)
	{
		if (strcmp(TYPE_KEYS[i], token))
		{
			return true;
		}
	}
	return false;
}
bool Parser::isOp(const char &tmp)
{
	for (int i = 0; i < 4; i++)
	{
		if (OP_KEYS[i] == tmp)
		{
			return true;
		}
	}
	return false;
}

void Parser::parser(const std::string &inContents)
{
	m_contents = inContents;

	int len = m_contents.length();
	while (m_currIndex < len - 1)
	{
		this->statement();
	}
}

char Parser::getNextChar() 
{
	return m_contents[m_currIndex + 1];
}

char Parser::getCurrChar()
{
	return m_contents[m_currIndex];
}

void Parser::toNext() 
{
	m_currIndex++;
}

char* Parser::getToken()
{
	char token[32] = { '0' };
	char curr = this->getCurrChar();
	
	if (curr == ' ' || curr == '\t')
	{
		this->toNext();
	}
	if (curr == '\n')
	{
		m_lineCount++;
	}

	int count = 0;
	curr = this->getCurrChar();
	while (this->isChar(curr))
	{
		token[count] = curr;
		count++;

		this->toNext();
		curr = this->getCurrChar();
	}

	return token;
}

void Parser::statement()
{
	char currToken[32] = { '0' };
	memcpy(currToken, this->getToken(), 32);

	if (this->isKeys(currToken))
	{
		printf("Parser: the curr key is %s\n", currToken);
		this->expression();
	}
	else if (this->isType(currToken))
	{
		printf("Parser: the curr baseType is %s\n", currToken);
	}
}

void Parser::expression()
{
	this->term();

	while (true)
	{
		char curr = this->getCurrChar();
		if (curr == '+')
		{
			this->term();
		}
		else if (curr == '-')
		{
			this->term();
		}
		else
		{
			break;
		}
	}
}

void Parser::term()
{
	this->factor();
	while (true)
	{
		char curr = this->getCurrChar();
		if (curr == '*')
		{
			this->factor();
		}
		else if (curr == '/')
		{
			this->factor();
		}
		else
		{
			break;
		}
	}
}

void Parser::factor()
{ 
	while (this->getCurrChar() == ' '|| this->getCurrChar() == '\t')
	{
		this->toNext();
	}

	if (this->isDight(this->getCurrChar()))
	{
		std::vector<int> arr;
		while (this->isDight(this->getCurrChar()))
		{
			int num = this->getCurrChar() - '0';
			arr.push_back(num);

			this->toNext();
		}

		size_t size = arr.size();
		int dight = 0;
		for (int i = 0; i < size; i++)
		{
			dight = dight * 10 + arr.at(i);
		}

		printf("Parser: the factor dight is %d\n", dight);
	}
	else
	{
		printf("Parser: the curr char is %c, not dight\n", this->getCurrChar());
	}
}