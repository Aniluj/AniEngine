#include "Camera.h"


Camera::Camera(Renderer* rendererPtr):Entity(rendererPtr)
{

}


Camera::~Camera()
{
}

void Camera::Walk(float forwardMovement)
{
	Translate(vectorPosition.x, vectorPosition.y, vectorPosition.z + forwardMovement);
	//renderer->SetViewMatrix()
}

void Camera::Strafe()
{

}