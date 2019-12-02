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

	glm::vec3 localScale;
	glm::vec3 right;
	glm::vec3 up;
	glm::vec3 forward;
	//glm::mat4 worldMatrix;
	glm::mat4 model;
	glm::mat4 scallingMatrix;
	glm::mat4 localRotation;
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

	glm::vec3 GetPosition();

	void RotateX(float angle);
	void RotateY(float angle);
	void RotateZ(float angle);

	glm::vec3 GetRight();
	glm::vec3 GetUp();
	glm::vec3 GetForward();

	void UpdateModel();
	void UpdateRotationMatrix();
	void UpdateDirectionVectors();

	void Start(const char * componentName) override;
	void Update() override;
	void Draw() override;
	glm::mat4& GetModel();
};

