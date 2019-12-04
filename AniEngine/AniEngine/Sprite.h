#pragma once

#include "Shape.h"
#include "Exports.h"
#include <iostream>
#include "BoundingCircle.h"
#include "BoundingBox.h"
#include "Renderer.h"
#include "Animation.h"
#include "glm\glm.hpp"

class ENGINEDLL_API Sprite : public Shape
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
	Sprite(
		Renderer * renderer,
		const char * imagepath,
		float massToSet,
		int  frameWidth,
		int  frameHeight,
		int  initialRow,
		int  initialColumn);
	Animation * testAnimation;
	BoundingBox * bbox;
	BoundingCircle* bcircle;
	void Draw() override;
	void UpdateDT(double & deltaTime);
	~Sprite();
};

