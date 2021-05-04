#pragma once
#include <string>

class Image 
{
public:
	Image();
	~Image();

	void loadFromFile(std::string filename);
private:
	int height;
	int width;
	int nrChannel;

	unsigned char* m_pData;
};