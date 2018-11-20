#pragma once

#include "Exports.h"
#include "Shape.h"
#include <iostream>
#include "glm\glm.hpp"

using namespace std;

class ENGINEDLL_API BoundingBox
{
public:
	BoundingBox(const char * tag, Shape* shape, bool isStaticValidation);
	~BoundingBox();

	Shape* receivedShape;

	bool isStatic;

	float mass;

	float width;
	float height;

	glm::vec3 vectorPosition;

	string bboxTag;
	void UpdateBoundingBoxModel(float width, float height, glm::vec3 entityVectorPosition, float massToSet);
};

