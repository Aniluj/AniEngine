#pragma once

#include "GameBase.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "Mesh.h"
#include "Sprite.h"
#include "CollisionManager.h"
#include "Tilemap.h"
#include "Camera.h"
#include "Input.h"
#include "BSP.h"
#include "Node.h"
#include "ScGraphObject.h"
#include "ScGraphShapeObject.h"
#include <iostream>
#include <time.h>

using namespace std;

class Game : public GameBase
{
private:
	int i;
	float timeLim = 4.0f;
	float cameraSpeed = 50.0f;
	float timer;
public:
	Game();
	~Game();
	Camera* camera;

	Triangle* triangle;
	Rectangle* rectangle;

	Mesh* M4Fusil;
	Mesh* Spider;

	Sprite* character;
	Sprite* enemy;

	Input* input;
	CollisionManager* collManager;
	Tilemap* tilemap;

	ScGraphObject* exampleObject;
	ScGraphShapeObject* shapeExampleObject;

	Node* nWeap1Root;
	Node * nWeap1;
	MeshComponentLoader * nWeap1Mesh;

	Node* nWeap2Root;
	Node * nWeap2;
	MeshComponentLoader * nWeap2Mesh;

	Node* nWeap3Root;
	Node * nWeap3;
	MeshComponentLoader * nWeap3Mesh;

	Node* nWeap4Root;
	Node * nWeap4;
	MeshComponentLoader * nWeap4Mesh;

	Node* nWeap5Root;
	Node * nWeap5;
	MeshComponentLoader * nWeap5Mesh;

	Node* sceneBSPTest;
	Node * nObjects;
	Node* nBSP1;
	BSP * BSPComponent1;
	Node* nBSP2;
	BSP * BSPComponent2;
	Node* nBSP3;
	BSP * BSPComponent3;
protected:
	bool OnStart() override;
	bool OnStop() override;
	bool OnUpdate() override;
	void OnDraw() override;
};

