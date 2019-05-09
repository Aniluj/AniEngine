#pragma once
#include "Mesh.h"
#include "Material.h"

class ENGINEDLL_API Cube : public Mesh
{
public:
	Cube(Renderer * rendererPtr);
	~Cube();
	void Draw() override;
};

