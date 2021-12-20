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
关于obj 文件的简单解释
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
		"v " 表示空间坐标
		"vt" 表示纹理坐标
		"vn" 表示法线向量
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
		"f" 表示face 三个顶点索引所构成(一个顶点索引由空间坐标 + 纹理坐标 + 法线向量)
		*/
		else if (!line.compare(0, 2, "f"))
		{

		}
	}
}