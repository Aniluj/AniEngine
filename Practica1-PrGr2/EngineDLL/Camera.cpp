#include "Camera.h"


Camera::Camera(Renderer* rendererPtr):Entity(rendererPtr)
{
	int hola = 0;

	/*vectorPosition.x = 480;
	vectorPosition.y = 320;
	vectorPosition.z = 960;*/

	Translate(480, 320, 960);

	center.x = 0;
	center.y = 0;
	center.z = 0;

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

	center.y = vectorPosition.y + rotationX[1][1];
	center.z = vectorPosition.z + rotationX[1][2];

	renderer->SetViewMatrix(glm::vec3(vectorPosition.x, vectorPosition.y, vectorPosition.z),
							glm::vec3(vectorPosition.x, center.y, center.z),
							glm::vec3(0, 1, 0));
}

void Camera::Yaw(float yRotation)
{
	RotateY(yRotation);

	center.x += rotationY[0][0];
	center.z += rotationY[0][2];

	cout << center.x << endl;
	cout << center.z << endl;

	renderer->SetViewMatrix(glm::vec3(vectorPosition.x, vectorPosition.y, vectorPosition.z),
		glm::vec3(vectorPosition.x + center.x, vectorPosition.y, vectorPosition.z + center.z),
		glm::vec3(0, 1, 0));
}

void Camera::Roll(float zRotation)
{
	RotateZ(zRotation);

	renderer->SetViewMatrix(glm::vec3(vectorPosition.x, vectorPosition.y, vectorPosition.z),
							glm::vec3(center.x, center.y, center.z - 1),
							glm::vec3(rotationZ[0][0], rotationZ[1][0], 0));
}

void Camera::Draw()
{

}