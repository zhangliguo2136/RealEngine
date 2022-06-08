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

// 执行函数
void execfunction(std::string func, std::vector<std::string> args)
{
	// 执行函数
	if (func == "print")
	{
		for (auto iter : args)
		{
			printf("%s", iter.c_str());
		}

		printf("\n");
	}
}

// 是否是控制语句
bool isControlToken(std::string token)
{
	if (token == "if")
		return true;

	return false;
}

// 分割字符串
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

// 计算表达式
void eval(Expression expr)
{
	// 赋值表达式
	// 算数表达式
	// 关系表达式

	std::vector<std::string> vs;
	vs.pop_back();
}

// 执行语句
void exec(Statement stat)
{
	std::string token = stat.getToken();

	// 控制语句
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

		// 函数执行语句
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