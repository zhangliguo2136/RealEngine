#pragma once
#include <string>

class Image 
{
public:
	Image(std::string filename);
	~Image();

	void loadFromFile(std::string filename);
private:
	int height;
	int width;
	int nrChannel;

	unsigned char* m_pData;

private:
	void loadFromMemoryTest(std::string filename);
};