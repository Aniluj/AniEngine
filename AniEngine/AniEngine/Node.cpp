#include "Node.h"



Node::Node(Renderer * rendererPtr)
{
	childNodes = new list<Node*>();
	components = new list<Component*>();
	renderer = rendererPtr;
	transform = new Transform();
	transform->componentName = "transform";
	components->push_back(transform);
}

Node::~Node()
{
	if (childNodes->size > 0)
	{
		for (auto aux : *childNodes)
		{
			delete aux;
		}
		childNodes->clear();
	}
	delete childNodes;
}

void Node::AddComponent(Component * component)
{
	components->push_back(component);
}

void Node::RemoveComponent(Component * component)
{
	components->remove(component);
	delete component;
}

void Node::AddChild(Node * childNode)
{
	childNodes->push_back(childNode);
	childNode->parent = this;
}

void Node::RemoveChild(Node * childNode)
{
	childNodes->remove(childNode);
	delete childNode;
}

void Node::Update()
{

	glm::mat4 savedWorldMatrix = renderer->GetModelMatrix();
	renderer->MultiplyModel(transform->GetModel());
	transform->translationMatrix = transform->translationMatrix * parent->transform->translationMatrix;
	//transform->UpdateModel();
}

void Node::Draw()
{

}