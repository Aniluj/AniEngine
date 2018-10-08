#pragma once

#include "Exports.h"
#include <iostream>
#include "glm\glm.hpp"

class ENGINEDLL_API Texture
{
private:
	unsigned int textureID;
public:
	Texture(int width, int height, void * data);
	~Texture();
};

