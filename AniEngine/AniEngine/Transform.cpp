#include "Transform.h"



void Transform::UpdateModel()
{
	model = translationMatrix * (rotationX * rotationY * rotationZ) * scallingMatrix;
}

void Transform::Translate(float x, float y, float z)
{
	glm::vec3 vector3(x, y, z);

	localPosition = vector3;

	translationMatrix = glm::translate(glm::mat4(1.0f), vector3);

	UpdateModel();
}

void Transform::Scale(float x, float y, float z)
{
	glm::vec3 vector3(x, y, z);

	scallingMatrix = glm::scale(vector3);

	UpdateModel();
}

void Transform::RotateX(float angle)
{
	glm::vec3 vectorAxis;

	vectorAxis[0] = 1.0f;
	vectorAxis[1] = 0.0f;
	vectorAxis[2] = 0.0f;

	rotationX = glm::rotate(glm::mat4(1.0f), glm::radians(angle), vectorAxis);

	UpdateModel();
}

void Transform::RotateY(float angle)
{
	glm::vec3 vectorAxis;

	vectorAxis[0] = 0.0f;
	vectorAxis[1] = 1.0f;
	vectorAxis[2] = 0.0f;

	rotationY = glm::rotate(glm::mat4(1.0f), glm::radians(angle), vectorAxis);

	UpdateModel();
}

void Transform::RotateZ(float angle)
{
	glm::vec3 vectorAxis;

	vectorAxis[0] = 0.0f;
	vectorAxis[1] = 0.0f;
	vectorAxis[2] = 1.0f;

	rotationZ = glm::rotate(glm::mat4(1.0f), glm::radians(angle), vectorAxis);

	UpdateModel();
}
