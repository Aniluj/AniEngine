#include "MeshComponentLoader.h"

MeshComponentLoader::MeshComponentLoader()
{
}

void MeshComponentLoader::Start(const char * componentName, Node * rootNode, const char* path, const char* texturePath, Renderer* rendererPtr)
{
	Component::Start(componentName);
	componentType = MeshLoaderType;

	this->rootNode = rootNode;
	renderer = rendererPtr;
	FCBoundingBox = new FrustumCullingBoundingBox();
	LoadModel(path, texturePath);
}

void MeshComponentLoader::LoadModel(string path, string texturePath)
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

	FCBoundingBox->UpdateMaxsAndMins();
}

void MeshComponentLoader::ProcessNode(aiNode *node, const aiScene *scene, string texturePath)
{
	// process all the node's meshes (if any)

	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
		Node * meshChildNode = new Node(node->mName.C_Str, renderer);
		ProcessMesh(mesh, scene, texturePath);

		//meshChildNode = ProcessMesh(mesh, scene, texturePath);

		//rootNodeChild->AddChild(meshChildNode);

		//meshesData.push_back(ProcessMesh(mesh, scene, texturePath));
	}
	// then do the same for each of its children
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(node->mChildren[i], scene, texturePath);
	}
}

void MeshComponentLoader::ProcessMesh(aiMesh *mesh, const aiScene *scene, string texturePath)
{
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	glm::vec3 mins;
	glm::vec3 maxs;

	const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

	Node * childNode = new Node(mesh->mName.C_Str, renderer);

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

		childNode->FCBoundingBox->CheckMinsAndMax(vector);

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

	childNode->FCBoundingBox->UpdateMaxsAndMins();

	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];

		for (unsigned int j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	MeshComponent * meshComponent = new MeshComponent();
	string tempString = componentName.c_str();
	tempString.append(" meshComponent");
	meshComponent->Start(tempString.c_str(), FCBoundingBox, vertices, indices, renderer, texturePath);
	cout << meshComponent->componentName << endl;
	childNode->AddComponent(meshComponent);
}

void MeshComponentLoader::Draw()
{

}

void MeshComponentLoader::Update()
{
	Component::Update();
}

MeshComponentLoader::~MeshComponentLoader()
{
	delete FCBoundingBox;
}


