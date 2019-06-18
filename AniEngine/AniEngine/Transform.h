#pragma once

#include "Component.h"
#include "Exports.h"
#include "glm\glm.hpp"

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

class ENGINEDLL_API Transform : public Component
{
private:
	glm::vec3 localRotation;


	glm::vec3 localScale;
	//glm::mat4 worldMatrix;
	glm::mat4 model;
	glm::mat4 scallingMatrix;
	glm::mat4 rotationX;
	glm::mat4 rotationY;
	glm::mat4 rotationZ;
public:
	Transform();
	~Transform();

	glm::mat4 translationMatrix;

	glm::vec3 localPosition;
	//glm::vec3 worldPosition;

	void Scale(float x, float y, float z);
	void Translate(float x, float y, float z);
	void RotateX(float angle);
	void RotateY(float angle);
	void RotateZ(float angle);
	void UpdateModel();
	void Start(const char * componentName) override;
	void Update() override;
	void Draw() override;
	glm::mat4& GetModel();
};

