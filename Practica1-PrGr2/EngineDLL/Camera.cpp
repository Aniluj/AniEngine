#include "Camera.h"


Camera::Camera(Renderer* rendererPtr):Entity(rendererPtr)
{
	int hola = 0;
	vectorPosition.x = 480;
	vectorPosition.y = 320;
	vectorPosition.z = 960;

	renderer->SetProjectionMatrixToPerspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 1000.0f);
	renderer->SetViewMatrix(glm::vec3(vectorPosition.x, vectorPosition.y, vectorPosition.z), glm::vec3(480, 320, 0), glm::vec3(0, 1, 0));
}


Camera::~Camera()
{
}

void Camera::Walk(float forwardMovement)
{
	Translate(vectorPosition.x, vectorPosition.y, vectorPosition.z + forwardMovement);
	renderer->SetViewMatrix(glm::vec3(vectorPosition.x, vectorPosition.y, vectorPosition.z + forwardMovement), glm::vec3(vectorPosition.x, vectorPosition.y, 0), glm::vec3(0, 1, 0));
}

void Camera::Strafe(float horizontalMovement)
{
	Translate(vectorPosition.x + horizontalMovement, vectorPosition.y, vectorPosition.z);
	renderer->SetViewMatrix(glm::vec3(vectorPosition.x + horizontalMovement, vectorPosition.y, vectorPosition.z), glm::vec3(vectorPosition.x, vectorPosition.y, 0), glm::vec3(0, 1, 0));
}

void Camera::Draw()
{

}