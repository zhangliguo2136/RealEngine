#pragma once
#include <string>
#include "Logger.h"

//关键字列表
static char KEYS[4][32] = { "if", "else", "for", "while"};
static char TYPE_KEYS[4][32] = { "TValue", "TFunction", "TClass", "TObject" };
static char OP_KEYS[4] = { '+','-','*','/' };

class Parser
{
public:
	Parser();
	
	~Parser() {};

	void parser(const std::string &contents);

private:
	bool isChar(const char &tmp);
	bool isDight(const char &tmp);

	bool isKeys(const char token[32]);
	bool isType(const char token[32]);
	bool isOp(const char &tmp);

private:

	char getNextChar();

	char getCurrChar();

	void toNext();

	char* getToken();
private:
	// 语句
	void statement();
	// 表达式
	void expression();
	// term
	void term();
	// factor
	void factor();

private:
	char m_token[32] = { '0' };
	int m_lineCount = 0;

	// 当前读取的字符
	int m_currIndex = 0;

	std::string m_contents;
};