#pragma once

#include "Exports.h"
#include "Renderer.h"
#include "Entity.h"

class ENGINEDLL_API Camera : public Entity
{
private:
	glm::vec4 forward;
	glm::vec4 up;
	glm::vec4 right;
public:
	Camera(Renderer* rendererPtr);
	~Camera();
	void Walk(float forwardMovement);
	void Strafe(float horizontalMovement);
	void Pitch(float xRotation);
	void Yaw(float yRotation);
	void Roll(float zRotation);
	void Draw() override;
};

