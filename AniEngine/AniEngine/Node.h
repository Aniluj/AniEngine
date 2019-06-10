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
	list<Node*>* childNodes;
	list<Component*>* components;
	Renderer * renderer;
public:
	Node(Renderer * rendererPtr);
	~Node();

	Transform * transform;
	Node * parent;
	void AddComponent(Component * component);
	//Component* GetComponent(const char * componentName);
	void RemoveComponent(Component * component);
	void AddChild(Node * childNode);
	void RemoveChild(Node * childNode);
	void Update();
	void Draw();
};

