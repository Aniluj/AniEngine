#include "Transform.h"


Transform::Transform()
{
	localPosition = glm::vec3(0.0f);
	localRotation = glm::vec3(0.0f);
	localScale = glm::vec3(0.0f);
	worldPosition = glm::vec3(0.0f);
	model = glm::mat4(1.0f);
	translationMatrix = glm::mat4(1.0f);
	rotationX = glm::mat4(1.0f);
	rotationY = glm::mat4(1.0f);
	rotationZ = glm::mat4(1.0f);
	scallingMatrix = glm::mat4(1.0f);
}

void Transform::Start(const char * componentName)
{
	this->componentName = componentName;
}

void Transform::UpdateModel()
{
	model = translationMatrix * (rotationX * rotationY * rotationZ) * scallingMatrix;
}

glm::mat4& Transform::GetModel()
{
	return model;
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

Transform::~Transform()
{
}

