#include "MeshComponentLoader.h"

MeshComponentLoader::MeshComponentLoader()
{
}

void MeshComponentLoader::Start(const char * componentName, const char* path, const char* texturePath, Renderer* rendererPtr)
{
	Component::Start(componentName);
	componentType = MeshType;

	renderer = rendererPtr;
	bBox = new FrustumCullingBoundingBox;
	LoadModel(path, texturePath);

	//cout << componentName << endl;
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
	bBox->UpdateMaxsAndMins();
}

void MeshComponentLoader::ProcessNode(aiNode *node, const aiScene *scene, string texturePath)
{
	// process all the node's meshes (if any)
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
		//Node * loquito = ProcessMesh(mesh, scene, texturePath);
		//loquito->addChild(loquito);
		meshesData.push_back(ProcessMesh(mesh, scene, texturePath));
	}
	// then do the same for each of its children
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(node->mChildren[i], scene, texturePath);
	}
}

MeshData* MeshComponentLoader::ProcessMesh(aiMesh *mesh, const aiScene *scene, string texturePath)
{
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	glm::vec3 mins;
	glm::vec3 maxs;

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

void MeshComponentLoader::Draw()
{
	Plane * frustumPlanesPtr = renderer->GetFrustumPlanesPtr();
	
	cout << "MIN Y: " << bBox->mins.y << endl;
	cout << "MAX Y: " << bBox->maxs.y << endl;
	cout << endl;

	cout << "MIN X: " << bBox->mins.x << endl;
	cout << "MAX X: " << bBox->maxs.x << endl;
	cout << endl;

	cout << "MIN Z: " << bBox->mins.z << endl;
	cout << "MAX Z: " << bBox->maxs.z << endl;
	cout << endl;

	glm::vec4 algoRaro = renderer->GetModelMatrix() * bBox->bBoxVertices[7];
	glm::vec4 algoRaro2 = renderer->GetModelMatrix() * bBox->bBoxVertices[5];

	cout << "MAX Y Moved:  " << algoRaro.y << endl;
	cout << "MIN Y Moved:  " << algoRaro2.y << endl;
	cout << endl;

	cout << "MIN X Moved:  " << algoRaro.x << endl;
	cout << "MAX X Moved:  " << algoRaro2.x << endl;
	cout << endl;

	cout << "MAX Z Moved:  " << algoRaro.z << endl;
	cout << "MAX Z Moved:  " << algoRaro2.z << endl;
	cout << endl;

	//DrawBoundingBox();

	//for (int i = 0; i < 6; i++)
	//{
	//	bool allBehind = true;

	//	for (int j = 0; j < 8; j++)
	//	{
	//		if (renderer->ClassifyPoint(frustumPlanesPtr[i], renderer->GetModelMatrix() * bBox->bBoxVertices[j] /** renderer->GetModelMatrix()*/) == POSITIVE)
	//		{
	//			//cout << "CHECKEO EN MESH "  << i << "  " << frustumPlanesPtr[i].a << endl;
	//			allBehind = false;
	//			break;
	//		}
	//	}
	//	if (allBehind)
	//	{
	//		cout << "NO SE DIBUJAAAAAAAAAAAAAAAAAAAAAAAAA" << i << endl;
	//		
	//		return;
	//	}
	//}

	for (unsigned int i = 0; i < meshesData.size(); i++)
	{

		//
		meshesData[i]->Draw();
		//cout << "minX: " << bBox->maxY << endl;
		//cout << "X de cara frontal: " << bBox->bBoxVertices[2].x << endl;
		//cout << componentName << endl;
		//cout << "size of mesh data vector: " << meshesData.size() << endl;
	}
}

//void MeshComponent::DrawBoundingBox()
//{
//	BoundingBoxForDrawing fcNew = BoundingBoxForDrawing();
//
//	for (int i = 0; i < 8; i++)
//	{
//		fcNew.bBoxVertices[i] = bBox->bBoxVertices[i];
//	}
//
//	float* fcVertex = new float[12 * 3]
//	{
//		fcNew.bBoxVertices[5].x, fcNew.bBoxVertices[5].y, fcNew.bBoxVertices[5].z,
//		fcNew.bBoxVertices[1].x, fcNew.bBoxVertices[1].y, fcNew.bBoxVertices[1].z,
//		fcNew.bBoxVertices[7].x, fcNew.bBoxVertices[7].y, fcNew.bBoxVertices[7].z,
//
//		fcNew.bBoxVertices[1].x, fcNew.bBoxVertices[1].y, fcNew.bBoxVertices[1].z,
//		fcNew.bBoxVertices[7].x, fcNew.bBoxVertices[7].y, fcNew.bBoxVertices[7].z,
//		fcNew.bBoxVertices[3].x, fcNew.bBoxVertices[3].y, fcNew.bBoxVertices[3].z,
//
//		fcNew.bBoxVertices[4].x, fcNew.bBoxVertices[4].y, fcNew.bBoxVertices[4].z,
//		fcNew.bBoxVertices[0].x, fcNew.bBoxVertices[0].y, fcNew.bBoxVertices[0].z,
//		fcNew.bBoxVertices[6].x, fcNew.bBoxVertices[6].y, fcNew.bBoxVertices[6].z,
//
//		fcNew.bBoxVertices[0].x, fcNew.bBoxVertices[0].y, fcNew.bBoxVertices[0].z,
//		fcNew.bBoxVertices[6].x, fcNew.bBoxVertices[6].y, fcNew.bBoxVertices[6].z,
//		fcNew.bBoxVertices[2].x, fcNew.bBoxVertices[2].y, fcNew.bBoxVertices[2].z,
//	};
//
//	float* verticesColorData = new float[3 * 12]
//	{
//		0.0f, 0.0f, 0.0f,
//		0.0f, 0.0f, 0.0f,
//		0.0f, 0.0f, 0.0f,
//
//		0.0f, 0.0f, 0.0f,
//		0.0f, 0.0f, 0.0f,
//		0.0f, 0.0f, 0.0f,
//
//		0.0f, 0.0f, 0.0f,
//		0.0f, 0.0f, 0.0f,
//		0.0f, 0.0f, 0.0f,
//
//		0.0f, 0.0f, 0.0f,
//		0.0f, 0.0f, 0.0f,
//		0.0f, 0.0f, 0.0f,
//	};
//
//	vector<unsigned int> indices{
//		0, 1, 2,
//		3, 4, 5,
//		6, 7, 8,
//		9,10,11
//	};
//
//	unsigned int id = renderer->GenBuffer(sizeof(float) * 12 * 3, fcVertex);
//	unsigned int colorId = renderer->GenBuffer(sizeof(float) * 12 * 3, verticesColorData);
//	unsigned int elementsId = renderer->GenElementBuffer(sizeof(unsigned int) * indices.size(), &indices.at(0));
//
//	renderer->BindBuffer(id, 0);
//	renderer->BindTexture(colorId);
//	renderer->BindElementBuffer(elementsId);
//	renderer->DrawElementBuffer(elementsId);
//}

void MeshComponentLoader::Update()
{
	Component::Update();
}

MeshComponentLoader::~MeshComponentLoader()
{
	delete bBox;
}


