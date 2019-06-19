#include "ScGraphObject.h"



ScGraphObject::ScGraphObject(Renderer * rendererPtr)
{
	renderer = rendererPtr;

	rootNode = new Node(renderer);
	rootNode->transform->Translate(0, 0, 0);

	M4 = new Node(renderer);
	M4Mesh = new MeshComponent();
	M4->transform->RotateZ(90);
	M4->transform->RotateX(-90);
	M4->transform->Translate(480, 370, 1200);
	M4Mesh->Start("M4Mesh", "M4A1/M4A1.FBX", "M4A1/M4A1Tex.bmp", renderer, M4->transform->GetModel());
	M4->AddComponent(M4Mesh);

	spider = new Node(rendererPtr);
	spiderMesh = new MeshComponent();
	spider->transform->Translate(480, 305, 1200);
	//spider->transform->Translate(480, 305, 1200);
	spiderMesh->Start("spiderMesh", "Spider/spider.obj", "Spider/SpiderTex.bmp", renderer, spider->transform->GetModel());
	spider->AddComponent(spiderMesh);

	M4->AddChild(spider);
	rootNode->AddChild(M4);
}


ScGraphObject::~ScGraphObject()
{
	delete spiderMesh;
	delete spider;
	delete M4Mesh;
	delete M4;
	delete rootNode;
}

void ScGraphObject::Draw()
{
	rootNode->Draw();
}
