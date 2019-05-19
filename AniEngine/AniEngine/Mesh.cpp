#include "Mesh.h"


Mesh::Mesh(const char* path, Renderer* rendererPtr):Entity(rendererPtr)
{
	LoadModel(path);
}

void Mesh::LoadModel(string path)
{
	Assimp::Importer import;
	const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);


	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		cout << "ERROR::ASSIMP::" << import.GetErrorString() << endl;
		return;
	}
	directory = path.substr(0, path.find_last_of('/'));


	ProcessNode(scene->mRootNode, scene);
}

void Mesh::ProcessNode(aiNode *node, const aiScene *scene)
{
	// process all the node's meshes (if any)
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
		meshesData.push_back(ProcessMesh(mesh, scene));
	}
	// then do the same for each of its children
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(node->mChildren[i], scene);
	}
}

MeshData* Mesh::ProcessMesh(aiMesh *mesh, const aiScene *scene)
{
	vector<Vertex> vertices;
	vector<unsigned int> indices;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;

		const aiVector3D* pPos = &(mesh->mVertices[i]);

		glm::vec3 vector;

		vector.x = (float)pPos->x;
		vector.y = (float)pPos->y;
		vector.z = (float)pPos->z;
		vertex.Position = vector;

		//vector.x = mesh->mNormals[i].x;
		//vector.y = mesh->mNormals[i].y;
		//vector.z = mesh->mNormals[i].z;
		//vertex.Normal = vector;

		vertices.push_back(vertex);
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];

		for (unsigned int j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	return new MeshData(vertices, indices, renderer);
}

void Mesh::Draw()
{
	for (unsigned int i = 0; i < meshesData.size(); i++)
	{
		meshesData[i]->Draw(model);
		//cout << "size of mesh data vector: " << meshesData.size() << endl;
	}
}

Mesh::~Mesh()
{
}
