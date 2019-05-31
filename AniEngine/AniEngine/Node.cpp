#include "Node.h"



Node::Node(Renderer * rendererPtr)
{
	renderer = rendererPtr;
}


Node::~Node()
{
}

void Node::AddComponent(Component * component)
{
	components->push_back(component);
}

void Node::RemoveComponent(Component * component)
{
	components->remove(component);
}

void Node::AddChild(Node * childNode)
{
	childNodes->push_back(childNode);
}

void Node::RemoveChild(Node * childNode)
{
	childNodes->remove(childNode);
}

void Node::Update()
{

}

void Node::Draw()
{

}