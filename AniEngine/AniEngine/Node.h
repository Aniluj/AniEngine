#pragma once

#include "Exports.h"
#include "Component.h"
#include "MeshComponent.h"
#include "Renderer.h"
#include "Transform.h"
#include "BSP.h"
#include <iostream>
#include <list>

class BSP;

using namespace std;

class ENGINEDLL_API Node
{
private:
	string name;
protected:
	list<Node*>* childNodes;
	list<Component*>* components;
	Renderer * renderer;
public:
	Node(string name, Renderer * rendererPtr);
	~Node();

	Transform * transform;
	Node * parent;
	FrustumCullingBoundingBox * FCBoundingBox;
	bool shouldDraw;

	void CheckPlanes();
	bool IsBehindPlane(glm::vec4& plane, Halfspace halfspace = POSITIVE);
	void CheckHalfspace(BSP* bsp);
	void AddComponent(Component * component);
	//Component* GetComponent(const char * componentName);
	void RemoveComponent(Component * component);
	void AddChild(Node * childNode);
	void RemoveChild(Node * childNode);
	void Update();
	void Draw();
};

