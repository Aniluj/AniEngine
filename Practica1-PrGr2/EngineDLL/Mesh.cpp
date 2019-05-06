#include "Mesh.h"



Mesh::Mesh(Renderer* rendererPtr):Entity(rendererPtr)
{
	meshData = new MeshData();
}


Mesh::~Mesh()
{
	delete meshData;
}
