#include "Entity.h"

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

Entity::Entity(Renderer* rendererPtr)
{
	renderer = rendererPtr;

	vectorPosition =   glm::vec3(0.0f);
	vectorRotation = glm::vec3(0.0f);
	vectorScale = glm::vec3(0.0f);
	model = glm::mat4(1.0f);
	translationMatrix = glm::mat4(1.0f);
	rotationX = glm::mat4(1.0f);
	rotationY = glm::mat4(1.0f);
	rotationZ = glm::mat4(1.0f);
	scallingMatrix = glm::mat4(1.0f);
	//diff = glm::vec3(4.0f, 2.0f, 1.2f) - glm::vec3(-1.0f, 23.0f, 1.2f);
	
	UpdateModel();
}

Entity::~Entity()
{
}

void Entity::UpdateModel()
{
	model = translationMatrix * (rotationX * rotationY * rotationZ) * scallingMatrix;
	
	//cout << glm::distance(glm::vec3(-1.0f, -23.0f, -1.2f), glm::vec3(4.0f, 2.0f, 1.2f)) << endl;
}

void Entity::Translate(float x, float y, float z)
{
	glm::vec3 vector3(x, y, z);

	vectorPosition = vector3;

	translationMatrix = glm::translate(glm::mat4(1.0f), vector3);

	UpdateModel();
}

void Entity::Scale(float x, float y, float z)
{
	glm::vec3 vector3(x, y, z);

	scallingMatrix = glm::scale(vector3);

	UpdateModel();
}

void Entity::RotateX(float angle)
{
	glm::vec3 vectorAxis;

	vectorAxis[0] = 1.0f;
	vectorAxis[1] = 0.0f;
	vectorAxis[2] = 0.0f;

	rotationX = glm::rotate(glm::mat4(1.0f), glm::radians(angle), vectorAxis);

	UpdateModel();
}

void Entity::RotateY(float angle)
{
	glm::vec3 vectorAxis;

	vectorAxis[0] = 0.0f;
	vectorAxis[1] = 1.0f;
	vectorAxis[2] = 0.0f;

	rotationY = glm::rotate(glm::mat4(1.0f), glm::radians(angle), vectorAxis);

	UpdateModel();
}

void Entity::RotateZ(float angle)
{
	glm::vec3 vectorAxis;

	vectorAxis[0] = 0.0f;
	vectorAxis[1] = 0.0f;
	vectorAxis[2] = 1.0f;

	rotationZ = glm::rotate(glm::mat4(1.0f), glm::radians(angle), vectorAxis);

	UpdateModel();
}
