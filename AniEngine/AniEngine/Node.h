#pragma once

#include "Exports.h"
#include "Component.h"
#include "MeshComponent.h"
#include "Renderer.h"
#include "Transform.h"
#include <iostream>
#include <list>

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
	void AddComponent(Component * component);
	//Component* GetComponent(const char * componentName);
	void RemoveComponent(Component * component);
	void AddChild(Node * childNode);
	void RemoveChild(Node * childNode);
	void Update();
	void Draw();
};

