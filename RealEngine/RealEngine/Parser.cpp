#include "Parser.h"

Statement::Statement(std::string s)
{
	_content = s;
	_length = s.length();
}


std::string Statement::getToken() 
{
	while (true)
	{
		auto ch = getCurrChar();

		if (ch == '\t' || ch == '\n' || ch == ' ')
		{
			this->skip();
		}
		else
		{
			break;
		}
	}

	std::string token;

	while (true)
	{	
		auto ch = getCurrChar();

		if (ch != '\t' && ch != '\n' && ch != ' ')
		{
			if (isChar(ch))
			{
				token.push_back(ch);
				
				this->skip();
			}
			else
			{
				break;
			}
		}
		else
		{
			break;
		}
	}

	return token;
}
const char Statement::getCurrChar() 
{
	return _content[_currIndex];
}

std::string Statement::getContent()
{
	return _content;
}

void Statement::skip() 
{
	_currIndex++;
}

void Statement::skipSpace()
{
	if (_content[_currIndex] == ' ' || _content[_currIndex] == '\t'|| _content[_currIndex] == '\n')
	{
		_currIndex++;
	}
}


Expression::Expression(std::string s)
{
	_content = s;
}

std::string Expression::getContent()
{
	return _content;
}

// ִ�к���
void execfunction(std::string func, std::vector<std::string> args)
{
	// ִ�к���
	if (func == "print")
	{
		for (auto iter : args)
		{
			printf("%s", iter.c_str());
		}

		printf("\n");
	}
}

// �Ƿ��ǿ������
bool isControlToken(std::string token)
{
	if (token == "if")
		return true;

	return false;
}

// �ָ��ַ���
std::vector<std::string> split(std::string s, const char split)
{
	std::istringstream iss(s);
	std::vector<std::string> result;

	std::string token;
	while (getline(iss, token, split))
	{
		std::string res = token;
		result.push_back(res);
	}

	return result;
}

// ������ʽ
void eval(Expression expr)
{
	// ��ֵ���ʽ
	// �������ʽ
	// ��ϵ���ʽ

	std::vector<std::string> vs;
	vs.pop_back();
}

// ִ�����
void exec(Statement stat)
{
	std::string token = stat.getToken();

	// �������
	if (isControlToken(token))
	{
		stat.skipSpace();
		auto ch = stat.getCurrChar();

		if (ch == '(')
		{
			stat.skip();

			std::string expr;
			while (true)
			{
				ch = stat.getCurrChar();

				if (ch != ')')
				{
					expr.push_back(ch);
					stat.skip();
				}
				else
				{
					stat.skip();
					break;
				}
			}

			eval(Expression(expr));
		}
	}

	else
	{
		auto ch = stat.getCurrChar();

		// ����ִ�����
		if (ch == '(')
		{
			stat.skip();

			std::string expr;
			while (true)
			{
				ch = stat.getCurrChar();

				if (ch != ')')
				{
					expr.push_back(ch);
					stat.skip();
				}
				else
				{
					stat.skip();
					break;
				}
			}

			auto func = token;
			auto args = split(expr, ',');

			execfunction(func, args);
		}

		else
		{
			eval(Expression(stat.getContent()));
		}
	}
}