#include "MeshComponent.h"



MeshComponent::MeshComponent()
{
}

void MeshComponent::Start(const char * componentName, const char* path, const char* texturePath, Renderer* rendererPtr, glm::mat4 & modelRef)
{
	Component::Start(componentName);
	componentType = MeshType;

	model = &modelRef;
	renderer = rendererPtr;
	LoadModel(path, texturePath);

	//cout << componentName << endl;
}

void MeshComponent::LoadModel(string path, string texturePath)
{
	Assimp::Importer import;
	const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);


	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		cout << "ERROR::ASSIMP::" << import.GetErrorString() << endl;
		return;
	}
	directory = path.substr(0, path.find_last_of('/'));


	ProcessNode(scene->mRootNode, scene, texturePath);
}

void MeshComponent::ProcessNode(aiNode *node, const aiScene *scene, string texturePath)
{
	// process all the node's meshes (if any)
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
		meshesData.push_back(ProcessMesh(mesh, scene, texturePath));
	}
	// then do the same for each of its children
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(node->mChildren[i], scene, texturePath);
	}
}

MeshData* MeshComponent::ProcessMesh(aiMesh *mesh, const aiScene *scene, string texturePath)
{
	vector<Vertex> vertices;
	vector<unsigned int> indices;

	const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;

		const aiVector3D* pPos = &(mesh->mVertices[i]);
		const aiVector3D* pTexCoord = mesh->HasTextureCoords(0) ? &(mesh->mTextureCoords[0][i]) : &Zero3D;
		const aiVector3D* pNormal = &(mesh->mNormals[i]);

		glm::vec3 vector;

		vector.x = (float)pPos->x;
		vector.y = (float)pPos->y;
		vector.z = (float)pPos->z;
		vertex.Position = vector;

		vector.x = (float)pNormal->x;
		vector.y = (float)pNormal->y;
		vector.z = (float)pNormal->z;
		vertex.Normal = vector;

		glm::vec2 vec;

		vec.x = (float)pTexCoord->x;
		vec.y = (float)pTexCoord->y;
		vertex.TexCoords = vec;

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

	return new MeshData(vertices, indices, renderer, texturePath);
}

void MeshComponent::Draw()
{
	for (unsigned int i = 0; i < meshesData.size(); i++)
	{
		meshesData[i]->Draw(*model);
		//cout << componentName << endl;
		//cout << "size of mesh data vector: " << meshesData.size() << endl;
	}
}

void MeshComponent::Update()
{
	Component::Update();
}

MeshComponent::~MeshComponent()
{
}
