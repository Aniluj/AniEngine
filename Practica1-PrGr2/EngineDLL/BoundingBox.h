#pragma once

#include "Exports.h"
#include "Shape.h"
#include <iostream>
#include "glm\glm.hpp"

using namespace std;

class ENGINEDLL_API BoundingBox
{
private:
	float width;
	float height;
public:
	BoundingBox(const char * tag);
	~BoundingBox();

	glm::vec3 vectorPosition;
	glm::mat4 translationMatrix;
	glm::mat4 rotationX;
	glm::mat4 rotationY;
	glm::mat4 rotationZ;
	glm::mat4 model;

	string bboxTag;
	void UpdateBoundingBoxModel(float width, float height, glm::vec3 entityVectorPosition, glm::mat4 entityRotationX, glm::mat4 entityRotationY, glm::mat4 entityRotationZ);
};

