#include "FileUtil.h"

#include <fstream>
#include <sstream>
#include <stdexcept>

std::string getFileContents(const std::string &filePath) 
{
	std::ifstream infile(filePath);

	if (!infile.is_open())
	{
		throw std::runtime_error("Unable to open file: " + filePath);
	}

	std::stringstream stream;
	stream << infile.rdbuf();

	return stream.str();
}

/*
����obj �ļ��ļ򵥽���
https://blog.csdn.net/qq_26900671/article/details/81739977
*/
void getObjModelContents(const std::string &filePath)
{
	std::ifstream infile(filePath);

	if (!infile.is_open())
	{
		throw std::runtime_error("Unable to open file: " + filePath);
	}

	std::string line;
	while (!infile.eof())
	{
		std::getline(infile, line);

		std::istringstream iss(line.c_str());
		/*
		"v " ��ʾ�ռ�����
		"vt" ��ʾ��������
		"vn" ��ʾ��������
		*/
		if (!line.compare(0, 2, "v "))
		{
		}
		else if (!line.compare(0, 2, "vt"))
		{
		}
		else if (!line.compare(0, 2, "vn"))
		{
		}
		/*
		"f" ��ʾface ������������������(һ�����������ɿռ����� + �������� + ��������)
		*/
		else if (!line.compare(0, 2, "f"))
		{

		}
	}
}