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

	Node* Weapon1Root;
	Node * Weapon1;
	MeshComponentLoader * Weapon1Mesh;

	Node* Weapon2Root;
	Node * Weapon2;
	MeshComponentLoader * Weapon2Mesh;

	Node* Weapon3Root;
	Node * Weapon3;
	MeshComponentLoader * Weapon3Mesh;

	Node* Weapon4Root;
	Node * Weapon4;
	MeshComponentLoader * Weapon4Mesh;

	Node* Weapon5Root;
	Node * Weapon5;
	MeshComponentLoader * Weapon5Mesh;

	Node* sceneBSPTest;
	Node * sceneObjects;
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

