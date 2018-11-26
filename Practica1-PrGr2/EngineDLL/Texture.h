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
	/*int frameWidth;
	int frameHeight;
	int row;
	int column;*/
	float minU;
	float maxU;
	float minV;
	float maxV;
public:
	Texture(Renderer * renderer, const char * imagepath, float massToSet, int frameWidth, int frameHeight, int row, int column);
	BoundingBox* bbox;
	BoundingCircle* bcircle;
	void Draw() override;
	~Texture();
};

