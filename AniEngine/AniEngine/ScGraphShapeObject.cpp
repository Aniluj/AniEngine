#include "ScGraphShapeObject.h"



ScGraphShapeObject::ScGraphShapeObject(Renderer * rendererPtr) : Node(rendererPtr)
{
	renderer = rendererPtr;

	triangle = new Node(renderer);
	triangle->transform->Translate(750, 400, 1000);
	shapeTriangle = new ShapeComponent();
	shapeTriangle->Start("shapeTriangle", renderer, 3, &triangle->transform->GetModel());
	shapeTriangle->SetMaterial("Shaders/VertexShader.txt", "Shaders/FragmentShader.txt");
	shapeTriangle->SetG_Vertex_Buffer_Data(
										   new float[shapeTriangle->GetVertexCount() * 3]
										   {
										   	-50.0f, -50.0f, 0.0f,
										   	50.0f, -50.0f, 0.0f,
										   	0.0f,  50.0f, 0.0f,
										   }
										   );
	triangle->AddComponent(shapeTriangle);

	AddChild(triangle);
}


ScGraphShapeObject::~ScGraphShapeObject()
{
	delete triangle;
}
