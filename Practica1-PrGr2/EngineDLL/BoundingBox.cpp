#include "BoundingBox.h"

BoundingBox::BoundingBox(const char * tag)
{
	bboxTag = tag;

	vertexPositions = new float[12]
	{
		-1.0f,1.0f, 0.0f,
		1.0f,1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f,0.0f,
	};

	vectorPosition = glm::vec3(0.0f);
	vectorRotation = glm::vec3(0.0f);
	model = glm::mat4(1.0f);
	translationMatrix = glm::mat4(1.0f);
	rotationX = glm::mat4(1.0f);
	rotationY = glm::mat4(1.0f);
	rotationZ = glm::mat4(1.0f);
}


BoundingBox::~BoundingBox()
{
	delete[] vertexPositions;
}

void BoundingBox::UpdateBoundingBoxModel(
	glm::vec3 entityVectorPosition,
	glm::mat4 entityTranslationMatrix,
	glm::mat4 entityRotationX,
	glm::mat4 entityRotationY,
	glm::mat4 entityRotationZ)
{
	vectorPosition = entityVectorPosition;
	translationMatrix = entityTranslationMatrix;
	rotationX = entityRotationX;
	rotationY = entityRotationY;
	rotationZ = entityRotationZ;

	//model = translationMatrix * (rotationX*rotationY*rotationZ);
}
