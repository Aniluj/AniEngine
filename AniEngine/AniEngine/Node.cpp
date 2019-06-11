#include "Node.h"



Node::Node(Renderer * rendererPtr)
{
	childNodes = new list<Node*>();
	components = new list<Component*>();
	renderer = rendererPtr;
	transform = new Transform();
	transform->Start("transform");
	components->push_back(transform);
}

Node::~Node()
{
	if (childNodes->size() > 0)
	{
		for (Node* aux : *childNodes)
		{
			delete aux;
		}
		childNodes->clear();
	}
	delete childNodes;

	if (components->size() > 0)
	{
		for (Component* aux : *components)
		{
			delete aux;
		}
		components->clear();
	}
	delete components;
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
}

void Node::Draw()
{
	glm::mat4 savedWorldMatrix = renderer->GetModelMatrix();
	renderer->MultiplyModel(transform->GetModel());

	if (parent)
	{
		glm::mat4 & modelMatrix = transform->GetModel();
		//modelMatrix = transform->GetModel() * renderer->GetModelMatrix();
		cout << "Antes: " << parent->transform->localPosition.y << endl;
		cout << "Antes: " << transform->localPosition.y << endl;
		modelMatrix = renderer->GetModelMatrix() * transform->GetModel();
		cout << "Despues: " << transform->localPosition.z << endl;
		cout << "Despues: " << parent->transform->localPosition.z << endl;
	}
	if (components->size() > 0)
	{
		for (auto nodePtr : *components)
		{
			nodePtr->Draw();
		}
	}
	if (childNodes->size() > 0)
	{
		for (auto nodePtr : *childNodes)
		{
			nodePtr->Draw();
		}
	}

	renderer->SetModelMatrix(savedWorldMatrix);
}