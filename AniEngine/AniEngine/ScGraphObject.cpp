#include "ScGraphObject.h"



ScGraphObject::ScGraphObject(Renderer * rendererPtr)
{
	renderer = rendererPtr;

	rootNode = new Node("rootNode", renderer);
	rootNode->transform->Translate(1, 1, 1);

	M4 = new Node("M4Node", renderer);
	M4Mesh = new MeshComponentLoader();
	M4->transform->RotateZ(90);
	M4->transform->RotateX(-90);
	M4->transform->Translate(0, 0, 20);
	M4Mesh->Start("M4Mesh", M4, "M4A1/M4A1.FBX", "M4A1/M4A1Tex.bmp", renderer);
	M4->AddComponent(M4Mesh);

	spider = new Node("spiderNode", rendererPtr);
	spiderMesh = new MeshComponentLoader();
	spider->transform->Translate(-300, 0, 20);
	spiderMesh->Start("spiderMesh", spider, "Spider/spider.obj", "Spider/SpiderTex.bmp", renderer);
	spider->AddComponent(spiderMesh);

	//rootNode->AddChild(M4);
	//rootNode->AddChild(spider);
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
	//rootNode->Update();
	//rootNode->Draw();
	M4->Update();
	M4->Draw();
	//spider->Draw();
}
