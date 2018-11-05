#pragma once

#include "Shape.h"
#include "Exports.h"
#include <iostream>
#include "BoundingBox.h"
#include "glm\glm.hpp"

class ENGINEDLL_API Texture : public Shape
{
private:
	unsigned int texture;
public:
	Texture(Renderer * renderer, const char * imagepath);
	BoundingBox* bbox;
	void Draw() override;
	~Texture();
};

