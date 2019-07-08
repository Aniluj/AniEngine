#include "MeshComponent.h"

BoundingBoxForDrawing::BoundingBoxForDrawing()
{

}

MeshComponent::MeshComponent()
{
}

void MeshComponent::Start(const char * componentName, const char* path, const char* texturePath, Renderer* rendererPtr)
{
	Component::Start(componentName);
	componentType = MeshType;

	renderer = rendererPtr;
	bBox = new BoundingBoxForDrawing;
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

		bBox->CheckMinsAndMax(vector);

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

void BoundingBoxForDrawing::CheckMinsAndMax(glm::vec3 newPositionsToCheck)
{
	if (!isFirstTimeSet)
	{
		if (minX > newPositionsToCheck.x) {
											minX = newPositionsToCheck.x;
											bBoxVertices[0].x = minX;
											bBoxVertices[2].x = minX;
											bBoxVertices[4].x = minX;
											bBoxVertices[6].x = minX;
										  }
		if (maxX < newPositionsToCheck.x) { 
											maxX = newPositionsToCheck.x;
											bBoxVertices[1].x = maxX;
											bBoxVertices[3].x = maxX;
											bBoxVertices[7].x = maxX;
										  }

		if (minY > newPositionsToCheck.y) {
											minY = newPositionsToCheck.y;
											bBoxVertices[2].y = minY;
											bBoxVertices[3].y = minY;
											bBoxVertices[6].y = minY;
											bBoxVertices[7].y = minY;
										  }
		if (maxY < newPositionsToCheck.y) {
											maxY = newPositionsToCheck.y;
											bBoxVertices[0].y = maxY;
											bBoxVertices[1].y = maxY;
											bBoxVertices[4].y = maxY;
											bBoxVertices[5].y = maxY;
										  }

		if (minZ > newPositionsToCheck.z) {
											minZ = newPositionsToCheck.z; 
											bBoxVertices[0].z = minZ;
											bBoxVertices[1].z = minZ;
											bBoxVertices[2].z = minZ;
											bBoxVertices[3].z = minZ;
										  }
		if (maxZ < newPositionsToCheck.z) {
											maxZ = newPositionsToCheck.z;
											bBoxVertices[4].z = maxZ;
											bBoxVertices[5].z = maxZ;
											bBoxVertices[6].z = maxZ;
											bBoxVertices[7].z = maxZ;
										  }
	}
	else
	{
		minX = newPositionsToCheck.x;
		minY = newPositionsToCheck.y;
		minZ = newPositionsToCheck.z;

		maxX = newPositionsToCheck.x;
		maxY = newPositionsToCheck.y;
		maxZ = newPositionsToCheck.z;

		bBoxVertices[0].x = minX;	bBoxVertices[1].x = maxX;
		bBoxVertices[0].y = maxY;	bBoxVertices[1].y = maxY;
		bBoxVertices[0].z = minZ;	bBoxVertices[1].z = minZ;
		bBoxVertices[0].w = 1;		bBoxVertices[1].w = 1;
		
		bBoxVertices[2].x = minX;	bBoxVertices[3].x = maxX;
		bBoxVertices[2].y = minY;	bBoxVertices[3].y = minY;
		bBoxVertices[2].z = minZ;	bBoxVertices[3].z = minZ;
		bBoxVertices[2].w = 1;		bBoxVertices[3].w = 1;


		bBoxVertices[4].x = minX;	bBoxVertices[5].x = maxX;
		bBoxVertices[4].y = maxY;	bBoxVertices[5].y = maxY;
		bBoxVertices[4].z = maxZ;	bBoxVertices[5].z = maxZ;
		bBoxVertices[4].w = 1;		bBoxVertices[5].w = 1;

		bBoxVertices[6].x = minX;	bBoxVertices[7].x = maxX;
		bBoxVertices[6].y = minY;	bBoxVertices[7].y = minY;
		bBoxVertices[6].z = maxZ;	bBoxVertices[7].z = maxZ;
		bBoxVertices[6].w = 1;		bBoxVertices[7].w = 1;

		isFirstTimeSet = false;
	}
}

void MeshComponent::Draw()
{
	for (unsigned int i = 0; i < meshesData.size(); i++)
	{
		meshesData[i]->Draw();
		cout << "minX: " << bBox->maxY << endl;
		cout << "X de cara frontal: " << bBox->bBoxVertices[2].x << endl;
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
	delete bBox;
}

BoundingBoxForDrawing::~BoundingBoxForDrawing()
{

}
