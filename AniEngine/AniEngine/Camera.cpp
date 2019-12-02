#include "Camera.h"


Camera::Camera(Renderer* rendererPtr):Entity(rendererPtr)
{
	forward = glm::vec4(0, 0, 1, 0);
	up = glm::vec4(0, 1, 0, 0);
	right = glm::vec4(1, 0, 0, 0);
	pos = glm::vec4(0, 0, 0, 1);

	fovy = glm::radians(45.0f);
	aspect = 4.0f / 3.0f;
	zNear = 0.1f;
	zFar = 400.0f;
	/*vectorPosition.x = 480;
	vectorPosition.y = 320;
	vectorPosition.z = 960;*/

	//Translate(480, 320, 1500);

	pos.x = 0;
	pos.y = 0;
	pos.z = -20;

	renderer->SetProjectionMatrixToPerspective(fovy, aspect, zNear, zFar);
	renderer->SetViewMatrix(pos, (glm::vec3)pos + (glm::vec3)forward, glm::vec3(0, 1, 0));

	UpdateValues();
}


Camera::~Camera()
{
}

void Camera::UpdateValues()
{
	renderer->SetFrustumPlanes(pos, forward, right, up, zNear, zFar, aspect, fovy);
}

glm::vec4 Camera::GetCameraPosition()
{
	return pos;
}

void Camera::Walk(float forwardMovement)
{
	Translate(pos, (glm::vec3)(forward * forwardMovement));

	renderer->SetViewMatrix(pos,
							(glm::vec3)pos + (glm::vec3)forward,
							(glm::vec3) up);

	UpdateValues();
}

void Camera::Strafe(float horizontalMovement)
{
	Translate(pos, (glm::vec3)(right * horizontalMovement));

	renderer->SetViewMatrix(pos,
							(glm::vec3)pos + (glm::vec3)forward,
							(glm::vec3) up);
	UpdateValues();
}

void Camera::Pitch(float xRotation)
{
	//RotateX(xRotation);

	//forward = rotationX * forward;
	forward = glm::rotate(glm::mat4(1.0f), glm::radians(xRotation), glm::vec3(right.x, right.y, right.z)) * forward;
	up = glm::rotate(glm::mat4(1.0f), glm::radians(xRotation), glm::vec3(right.x, right.y, right.z)) * up;
	//forward.y = vectorPosition.y + rotationX[1][1];
	//forward.z = vectorPosition.z + rotationX[1][2];

	renderer->SetViewMatrix(pos,
							(glm::vec3)pos + (glm::vec3)forward,
							(glm::vec3) up);
	UpdateValues();
}

void Camera::Yaw(float yRotation)
{
	//RotateY(yRotation);

	forward = glm::rotate(glm::mat4(1.0f), glm::radians(yRotation), glm::vec3(up.x, up.y, up.z)) * forward;
	right = glm::rotate(glm::mat4(1.0f), glm::radians(yRotation), glm::vec3(up.x, up.y, up.z)) * right;

	//forward = rotationY * forward;

	//forward.x += rotationY[0][0];
	//forward.z += rotationY[0][2];

	cout << forward.x << endl;
	cout << forward.z << endl;

	renderer->SetViewMatrix(pos,
							(glm::vec3)pos + (glm::vec3)forward,
							(glm::vec3) up);
	UpdateValues();
}

void Camera::Roll(float zRotation)
{
	//RotateZ(zRotation);

	right = glm::rotate(glm::mat4(1.0f), glm::radians(zRotation), glm::vec3(forward.x, forward.y, forward.z)) * right;
	up = glm::rotate(glm::mat4(1.0f), glm::radians(zRotation), glm::vec3(forward.x, forward.y, forward.z)) * up;

	//up = rotationZ * up;

	renderer->SetViewMatrix(pos,
							(glm::vec3)pos + (glm::vec3)forward,
							(glm::vec3) up);
	UpdateValues();
}

void Camera::Draw()
{
	/* ... */
}