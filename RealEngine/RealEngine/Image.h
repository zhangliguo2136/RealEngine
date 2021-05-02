#pragma once
#include <string>

class Image 
{
public:
	void loadFromFile(std::string filename);

private:
	int height;
	int width;

	char* m_pData;
};