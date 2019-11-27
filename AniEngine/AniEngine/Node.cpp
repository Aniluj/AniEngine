#include "Node.h"



Node::Node(string nodeName, Renderer * rendererPtr)
{
	name = nodeName;
	childNodes = new list<Node*>();
	components = new list<Component*>();
	FCBoundingBox = new FrustumCullingBoundingBox();
	renderer = rendererPtr;

	shouldDraw = true;

	transform = new Transform();
	transform->Start("transform");
	AddComponent(transform);
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

	if (parent)
	{
		parent->RemoveChild(this);
		parent = NULL;
	}
}

void Node::CheckPlanes()
{
	//if (!shouldDraw)
	//{
	//	return;
	//}

	if (FCBoundingBox->isFirstTimeSet == false)
	{
		glm::vec4 * frustumPlanesPtr = renderer->GetFrustumPlanesPtr();

		for (int i = 0; i < 6; i++)
		{
			bool allBehind = true;

			//cout << "A punto de clasificar puntos, vuelta N: " << i << endl;
			for (int j = 0; j < 8; j++)
			{
				if (renderer->ClassifyPoint(frustumPlanesPtr[i], renderer->GetModelMatrix() * glm::vec4(FCBoundingBox->bBoxVertices[j], 1.0f)) == POSITIVE)
				{
					allBehind = false;

					shouldDraw = true;
					break;
				}
			}
			if (allBehind)
			{
				cout << "NO SE DIBUJA ESTE NODO: " << name.c_str() << "||  con Plano: " << i << endl;

				shouldDraw = false;

				return;
			}
		}
	}
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
			parent->FCBoundingBox->CompareMinsAndMax(FCBoundingBox);
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

	if (FCBoundingBox->isFirstTimeSet == false)
	{
		FCBoundingBox->UpdateMaxsAndMins();
	}

	renderer->SetModelMatrix(savedWorldMatrix);
}