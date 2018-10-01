#pragma once

#include "Exports.h"
#include "Renderer.h"
#include "Material.h"
#include <glm\glm.hpp>

class ENGINEDLL_API Entity
{
protected:
	Renderer * renderer;

	glm::vec3 vectorPosition;
	glm::vec3 vectorRotation;
	glm::vec3 vectorScale;
	glm::mat4 translationMatrix;
	glm::mat4 model;
	glm::mat4 scallingMatrix;
	glm::mat4 rotationX;
	glm::mat4 rotationY;
	glm::mat4 rotationZ;
public:
	Material * material;

	Entity(Renderer* rendererPtr);
	~Entity();
	void Scale(glm::vec3 vector3);
	void Scale(float x, float y, float z);
	void Translate(glm::vec3 vector3);
	void Translate(float x, float y, float z);
	void RotateX(float angle);
	void RotateY(float angle);
	void RotateZ(float angle);
	void UpdateModel();
	void virtual Draw()=0;
};

