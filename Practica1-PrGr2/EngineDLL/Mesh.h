#pragma once
#include "Entity.h"
#include <vector>

using namespace std;

class ENGINEDLL_API Mesh : public Entity
{
protected:
	vector<unsigned int> indices;

	unsigned int elementBuffer;
public:
	Mesh(Renderer* rendererPtr);
	~Mesh();
};

