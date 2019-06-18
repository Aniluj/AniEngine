#include "Component.h"



Component::Component()
{
}


Component::~Component()
{
}

void Component::Start(const char* componentName)
{
	this->componentName = componentName;
	componentType = Default;
}

void Component::Draw()
{
}

void Component::Update()
{
}
