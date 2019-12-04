#pragma once

#include "Exports.h"
#include "glm\glm.hpp"
#include "Material.h"
#include "Transform.h"
#include "Component.h"
#include "Entity.h"
#include "Renderer.h"

class Camera;

class ENGINEDLL_API BSP : public Component
{
private:
	Transform* transform;
	Camera * gameCamera;
	Material * material;
	Renderer * renderer;

	glm::vec3 position;
	glm::vec3 forward;

	void UpdatePlane();

public:
	void Start(const char* componentName, Renderer * rendererPtr, Camera * gameCamera, Transform * transform);
	void Update() override;
	void Draw() override;
	void SetTransform(Transform* transform);

	glm::vec4 plane;
	Halfspace halfspace;

	BSP(/*const char* componentName, Renderer * rendererPtr, Camera * gameCamera*/);
	~BSP();
};

