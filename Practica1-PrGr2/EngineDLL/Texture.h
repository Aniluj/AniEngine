#pragma once

#include "Shape.h"
#include "Exports.h"
#include <iostream>
#include "glm\glm.hpp"

class ENGINEDLL_API Texture : public Shape
{
private:
	unsigned int textureID;
public:
	Texture(Renderer * renderer, const char * imagepath);
	void Draw() override;
	~Texture();
};

