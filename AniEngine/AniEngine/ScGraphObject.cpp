#include "ScGraphObject.h"



ScGraphObject::ScGraphObject(Renderer * rendererPtr)
{
	renderer = rendererPtr;

	M4 = new Node(rendererPtr);
	M4Mesh = new MeshComponent();
	M4Mesh->Start("M4Mesh", "M4A1/M4A1.FBX", "M4A1/M4A1Tex.bmp", rendererPtr, M4->transform->GetModel());
	M4->transform->RotateZ(90);
	M4->transform->RotateX(-90);
	M4->transform->Translate(480, 370, 1200);
	M4->AddComponent(M4Mesh);

	spider = new Node(rendererPtr);
	spiderMesh = new MeshComponent();
	spiderMesh->Start("spiderMesh", "Spider/spider.obj", "Spider/SpiderTex.bmp", rendererPtr, spider->transform->GetModel());
	spider->transform->Translate(480, 305, 1200);
	spider->AddComponent(spiderMesh);

	M4->AddChild(spider);
}


ScGraphObject::~ScGraphObject()
{
	delete M4Mesh;
	delete spider;
}

void ScGraphObject::Draw()
{
	M4->Draw();
}
