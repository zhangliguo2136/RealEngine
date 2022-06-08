#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <map>

class Statement
{
public:
	Statement(std::string s);

	std::string getToken();
	const char getCurrChar();
	void skip();
	void skipSpace();

	std::string getContent();
private:
	std::string _content;
	int _length = 0;

	int _currIndex = 0;
};

static bool isChar(const char ch)
{
	if (ch >= 'a'&& ch <= 'z')
	{
		return true;
	}
	else if (ch >= 'A'&&ch <= 'Z')
	{
		return true;
	}

	return false;
}

static bool isDight(const char ch)
{
	if (ch >= '0'&& ch <= '9')
	{
		return true;
	}

	return false;
}

class Expression
{
public:
	Expression(std::string s);

	std::string getContent();
private:
	std::string _content;
};


/*
@�������
@����ִ��
@���ʽ���
*/

// ִ�к���
void execfunction(std::string func, std::vector<std::string> args);

// �Ƿ��ǿ������
bool isControlToken(std::string token);

// �ָ��ַ���
std::vector<std::string> split(std::string s, const char split);

// ������ʽ
void eval(Expression expr);

// ִ�����
void exec(Statement stat);