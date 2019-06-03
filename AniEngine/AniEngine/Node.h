#pragma once

#include "Exports.h"
#include "Component.h"
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
	Transform * transform;
	Renderer * renderer;
public:
	Node(Renderer * rendererPtr);
	~Node();

	Node * parent;
	void AddComponent(Component * component);
	void RemoveComponent(Component * component);
	void AddChild(Node * childNode);
	void RemoveChild(Node * childNode);
	void Update();
	void Draw();
};

