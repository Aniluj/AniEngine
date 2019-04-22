#include "Camera.h"


Camera::Camera(Renderer* rendererPtr):Entity(rendererPtr)
{
	forward = glm::vec4(0, 0, -1, 0);
	up = glm::vec4(0, 1, 0, 0);

	/*vectorPosition.x = 480;
	vectorPosition.y = 320;
	vectorPosition.z = 960;*/

	Translate(480, 320, 960);

	renderer->SetProjectionMatrixToPerspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 1000.0f);
	renderer->SetViewMatrix(vectorPosition, glm::vec3(480, 320, -1), glm::vec3(0, 1, 0));

	//Pitch(180);
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

	forward = rotationX * forward;
	//forward.y = vectorPosition.y + rotationX[1][1];
	//forward.z = vectorPosition.z + rotationX[1][2];

	renderer->SetViewMatrix(vectorPosition,
							vectorPosition + (glm::vec3)forward,
							glm::vec3(0, 1, 0));
}

void Camera::Yaw(float yRotation)
{
	RotateY(yRotation);

	forward = rotationY * forward;

	//forward.x += rotationY[0][0];
	//forward.z += rotationY[0][2];

	cout << forward.x << endl;
	cout << forward.z << endl;

	renderer->SetViewMatrix(vectorPosition,
							vectorPosition + (glm::vec3)forward,
							glm::vec3(0, 1, 0));
}

void Camera::Roll(float zRotation)
{
	RotateZ(zRotation);

	up = rotationZ * up;

	renderer->SetViewMatrix(vectorPosition,
							vectorPosition + (glm::vec3)forward,
							(glm::vec3) up);
}

void Camera::Draw()
{

}