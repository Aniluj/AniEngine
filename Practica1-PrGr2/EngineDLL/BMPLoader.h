#pragma once

#include "Exports.h"
#include <iostream>
#include "glm\glm.hpp"

class ENGINEDLL_API BMPLoader
{
private:
	static unsigned char bmpHeader[54];
	static unsigned char * data;
	static unsigned int dataPos;
	static unsigned int width;
	static unsigned int height;
	static unsigned int imageSize;
	static unsigned int textureID;
	static FILE * file;
public:
	BMPLoader();
	~BMPLoader();
	static unsigned int LoadBMP(const char * imagepath, int & frameWidth, int & frameHeight, int & row, int & column, float & minU, float & maxU, float & minV, float & maxV);
};

