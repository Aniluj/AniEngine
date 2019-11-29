#pragma once

#include "Exports.h"
#include "glm\glm.hpp"
#include "Material.h"
#include "Transform.h"
#include "Renderer.h"
#include "Component.h"

class ENGINEDLL_API BSP : public Component
{
private:
	Transform* transform;
	Material* material;
	Renderer* renderer;

	glm::vec3 position;
	glm::vec3 forward;

	void UpdatePlane();

public:
	void Start(Renderer * rendererPtr);
	void Update() override;
	void Draw() override;
	void SetTransform(Transform* transform);

	glm::vec4 plane;
	Halfspace halfspace;

	BSP(Renderer * rendererPtr);
	~BSP();
};

