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
	bool shouldDraw;
protected:
	list<Node*>* childNodes;
	list<Component*>* components;
	Renderer * renderer;
public:
	Node(string nodeNamde, Renderer * rendererPtr);
	~Node();

	FrustumCullingBoundingBox * FCBoundingBox;
	Transform * transform;
	Node * parent;
	void AddComponent(Component * component);
	void CheckPlanes();
	//Component* GetComponent(const char * componentName);
	void RemoveComponent(Component * component);
	void AddChild(Node * childNode);
	void RemoveChild(Node * childNode);
	void Update();
	void Draw();
};

