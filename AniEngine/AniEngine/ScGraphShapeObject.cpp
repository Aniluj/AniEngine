#include "ScGraphShapeObject.h"



ScGraphShapeObject::ScGraphShapeObject(Renderer * rendererPtr) : Node(rendererPtr)
{
	renderer = rendererPtr;

	triangle = new Node(renderer);
	triangle->transform->Translate(750, 400, 920);
	triangleShape = new ShapeComponent();
	triangleShape->Start("triangleShape", renderer, 3, &triangle->transform->GetModel());
	triangleShape->SetMaterial("Shaders/VertexShader.txt", "Shaders/FragmentShader.txt");
	triangleShape->SetG_Vertex_Buffer_Data(
										   new float[triangleShape->GetVertexCount() * 3]
										   {
										   	-50.0f, -50.0f, 0.0f,
										   	50.0f, -50.0f, 0.0f,
										   	0.0f,  50.0f, 0.0f,
										   }
										   );
	triangle->AddComponent(triangleShape);

	sprite = new Node(renderer);
	sprite->transform->Translate(650, 400, 920);
	spriteShape = new ShapeComponent();
	spriteShape->Start("spriteShape", renderer, 4, &sprite->transform->GetModel());
	spriteShape->SetMaterial("Shaders/TextureTransformVertexShader.txt", "Shaders/TextureFragmentShader.txt");
	spriteShape->SetG_Vertex_Buffer_Data(new float[spriteShape->GetVertexCount() * 3]
										 {
										 	50.0f,50.0f, 0.0f,
										 	-50.0f,50.0f, 0.0f,
										 	50.0f, -50.0f, 0.0f,
										 	-50.0f, -50.0f,0.0f,
										 }
										 );
	spriteAnimation = new AnimationComponent();
	//spriteAnimation->Start("spriteAnimation", renderer, )

	AddChild(triangle);
	triangle->AddChild(sprite);
}


ScGraphShapeObject::~ScGraphShapeObject()
{
	delete triangle;
}
