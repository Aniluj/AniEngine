#include "BoundingBox.h"

BoundingBox::BoundingBox(const char * tag)
{
	bboxTag = tag;

	vectorPosition = glm::vec3(0.0f);
	model = glm::mat4(1.0f);
	translationMatrix = glm::mat4(1.0f);
	rotationX = glm::mat4(1.0f);
	rotationY = glm::mat4(1.0f);
	rotationZ = glm::mat4(1.0f);
}


BoundingBox::~BoundingBox()
{

}

void BoundingBox::UpdateBoundingBoxModel(
	float width,
	float height,
	glm::vec3 entityVectorPosition,
	glm::mat4 entityRotationX,
	glm::mat4 entityRotationY,
	glm::mat4 entityRotationZ)
{
	vectorPosition = entityVectorPosition;
	//model = translationMatrix * (rotationX*rotationY*rotationZ);
}