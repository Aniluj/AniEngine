#pragma once

#include "Shape.h"
#include "Exports.h"
#include <iostream>
#include "BoundingCircle.h"
#include "BoundingBox.h"
#include "Animation.h"
#include "glm\glm.hpp"

class ENGINEDLL_API Texture : public Shape
{
private:
	unsigned int texture;
	float mass;
	/*
	int frameWidth;
	int frameHeight;
	int row;
	int column;
	float minU;
	float maxU;
	float minV;
	float maxV;
	*/
	int spritesheetWidth;
	int spritesheetHeight;
	double dt;
	float animationSpeed;
public:
	Texture(
		Renderer * renderer,
		const char * imagepath,
		float massToSet,
		int  frameWidth,
		int  frameHeight,
		int  initialRow,
		int  initialColumn,
		double & deltaTime);
	Animation * testAnimation;
	BoundingBox * bbox;
	BoundingCircle* bcircle;
	void Draw() override;
	~Texture();
};

