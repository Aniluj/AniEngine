#include "Mesh.h"
#include "assimp/Importer.hpp"


Mesh::Mesh(Renderer* rendererPtr):Entity(rendererPtr)
{
	meshData = new MeshData();
}


void Mesh::Draw()
{

}

Mesh::~Mesh()
{
	delete meshData;
}
