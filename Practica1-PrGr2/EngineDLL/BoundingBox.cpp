#include "BoundingBox.h"

BoundingBox::BoundingBox(const char * tag, Shape* shape, bool isStaticValidation)
{
	bboxTag = tag;
	receivedShape = shape;
	vectorPosition = glm::vec3(0.0f);
	isStatic = isStaticValidation;
}


BoundingBox::~BoundingBox()
{
	
}

void BoundingBox::UpdateBoundingBoxModel(
	float widthParam,
	float heightParam, 
	glm::vec3 entityVectorPosition,
	float massToSet)
{
	vectorPosition = entityVectorPosition;
	width = widthParam;
	height = heightParam;
	mass = massToSet;
}