#include "Camera.h"


Camera::Camera(Renderer* rendererPtr):Entity(rendererPtr)
{
	int hola = 0;

	/*vectorPosition.x = 480;
	vectorPosition.y = 320;
	vectorPosition.z = 960;*/

	Translate(480, 320, 960);
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

void Camera::Pitch(float xRotation)
{
	RotateX(xRotation);

	renderer->SetViewMatrix(glm::vec3(vectorPosition.x, vectorPosition.y, vectorPosition.z),
							glm::vec3(vectorPosition.x, vectorPosition.y + sin(glm::radians(xRotation)), vectorPosition.z + cos(glm::radians(xRotation))),
							glm::vec3(0, 1, 0));

	cout << (vectorPosition.x, vectorPosition.y + sin(glm::radians(xRotation)), vectorPosition.z + cos(glm::radians(xRotation))) << endl;
}

void Camera::Yaw(float yRotation)
{
	RotateY(yRotation);
	
	renderer->SetViewMatrix(glm::vec3(vectorPosition.x, vectorPosition.y, vectorPosition.z),
							glm::vec3(vectorPosition.x + cos(glm::radians(yRotation)), vectorPosition.y, vectorPosition.z + sin(glm::radians(yRotation))),
							glm::vec3(0, 1, 0));
}

void Camera::Roll(float zRotation)
{
	RotateZ(zRotation);

	renderer->SetViewMatrix(glm::vec3(vectorPosition.x, vectorPosition.y, vectorPosition.z),
							glm::vec3(vectorPosition.x + asin(glm::radians(zRotation)), vectorPosition.y + acos(glm::radians(zRotation)), 0),
							glm::vec3(0, 1, 0));
}

void Camera::Draw()
{

}