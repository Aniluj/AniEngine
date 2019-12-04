#pragma once

#include "Exports.h"
#include "Entity.h"
#include "Renderer.h"
#include "Transform.h"


class ENGINEDLL_API Camera : public Entity
{
private:
	glm::vec4 forward;
	glm::vec4 up;
	glm::vec4 right;
	glm::vec4 pos;

	float fovy;
	float aspect;
	float zNear;
	float zFar;
public:
	Camera(Renderer* rendererPtr);
	~Camera();

	glm::vec4 GetCameraPosition();

	void Walk(float forwardMovement);
	void Strafe(float horizontalMovement);
	void Pitch(float xRotation);
	void Yaw(float yRotation);
	void Roll(float zRotation);
	void Draw() override;
	void UpdateValues();
};

