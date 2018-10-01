#pragma once

#include "Exports.h"
#include "Renderer.h"
#include "Material.h"

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

	Entity(Renderer* rendererPtr);
	~Entity();
	void Scale(float x, float y, float z);
	void Translate(float x, float y, float z);
	void RotateX(float angle);
	void RotateY(float angle);
	void RotateZ(float angle);
	void UpdateModel();
	void virtual Draw()=0;
};

