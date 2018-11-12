#pragma once

#include "Shape.h"
#include "Exports.h"
#include <iostream>
#include "BoundingCircle.h"
#include "BoundingBox.h"
#include "glm\glm.hpp"

class ENGINEDLL_API Texture : public Shape
{
private:
	unsigned int texture;
	float mass;
public:
	Texture(Renderer * renderer, const char * imagepath, float massToSet);
	BoundingBox* bbox;
	BoundingCircle* bcircle;
	void Draw() override;
	~Texture();
};

