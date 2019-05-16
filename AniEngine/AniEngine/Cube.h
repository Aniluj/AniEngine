#pragma once
#include "Mesh.h"
#include "Material.h"

class ENGINEDLL_API Cube : public Entity
{
public:
	Cube(Renderer * rendererPtr);
	~Cube();
	void Draw() override;
};

