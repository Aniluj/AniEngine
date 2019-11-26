#include "Node.h"



Node::Node(string nodeName, Renderer * rendererPtr)
{
	shouldDraw = true;

	childNodes = new list<Node*>();
	components = new list<Component*>();
	renderer = rendererPtr;
	transform = new Transform();
	transform->Start("transform");
	components->push_back(transform);
	name = nodeName;
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

void Node::CheckPlanes()
{
	glm::vec4 * frustumPlanesPtr = renderer->GetFrustumPlanesPtr();

	for (int i = 0; i < 6; i++)
	{
		bool allBehind = true;

		for (int j = 0; j < 8; j++)
		{
			if (renderer->ClassifyPoint(frustumPlanesPtr[i], renderer->GetModelMatrix() * FCBoundingBox->bBoxVertices[j]) == POSITIVE)
			{
				allBehind = false;
				shouldDraw = true;

				break;
			}
		}
		if (allBehind)
		{
			cout << "NO SE DIBUJA: " << name.c_str() << "||  con Plano: " << i << endl;

			shouldDraw = false;

			//cout << "A: " << frustumPlanesPtr[1].a << endl;
			//cout << "B: " << frustumPlanesPtr[1].b << endl;
			//cout << "C: " << frustumPlanesPtr[1].c << endl;
			//cout << "D: " << frustumPlanesPtr[1].d << endl;

			return;
		}
	}
}

void Node::Update()
{
	if (components->size() > 0)
	{
		for (auto nodePtr : *components)
		{
			nodePtr->Update();
		}
	}
	if (childNodes->size() > 0)
	{
		for (auto nodePtr : *childNodes)
		{
			nodePtr->Update();
		}
	}
	if (parent)
	{
		if (parent->FCBoundingBox->isFirstTimeSet == false)
		{
			parent->FCBoundingBox->CompareMinsAndMaxs(FCBoundingBox);
		}
	}
}

void Node::Draw()
{
	glm::mat4 savedWorldMatrix = renderer->GetModelMatrix();
	renderer->MultiplyModel(transform->GetModel());

	CheckPlanes();

	if (shouldDraw)
	{
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
	}


	renderer->SetModelMatrix(savedWorldMatrix);
}