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
	sprite->transform->Translate(500, 400, 920);
	spriteShape = new ShapeComponent();
	spriteShape->Start("spriteShape", renderer, 4, &sprite->transform->GetModel());
	spriteShape->SetMaterial("Shaders/TextureTransformVertexShader.txt", "Shaders/TextureFragmentShader.txt");
	spriteShape->SetG_Vertex_Buffer_Data(
										 new float[spriteShape->GetVertexCount() * 3]
										 {
										 	50.0f,50.0f, 0.0f,
										 	-50.0f,50.0f, 0.0f,
										 	50.0f, -50.0f, 0.0f,
										 	-50.0f, -50.0f,0.0f,
										 }
										 );
	spriteShape->SetG_UV_Buffer_Data(new float[spriteShape->GetVertexCount() * 2]);
	spriteShape->SetTexture("Test-Spritesheet.bmp", 32, 32);
	spriteAnimation = new AnimationComponent();
	spriteAnimation->Start("spriteAnimation",
						   renderer,
						   spriteShape->GetTexture(),
						   spriteShape->GetG_UV_Buffer_Data(), 
						   &spriteShape->GetUVBuffer(),
						   0.5f,
						   1,
						   1);
	spriteAnimation->AddFrame(2, 1);
	spriteAnimation->AddFrame(3, 1);
	spriteAnimation->AddFrame(4, 1);
	spriteAnimation->AddFrame(5, 1);
	spriteAnimation->AddFrame(6, 1);
	spriteAnimation->AddFrame(7, 1);
	spriteAnimation->AddFrame(8, 1);

	sprite->AddComponent(spriteAnimation);
	sprite->AddComponent(spriteShape);


	rectangle = new Node(renderer);
	rectangle->transform->Translate(300, 400, 920);
	rectangleShape = new ShapeComponent();
	rectangleShape->Start("rectangleShape", renderer, 4, &rectangle->transform->GetModel());
	rectangleShape->SetMaterial("Shaders/TransformVertexShader.txt", "Shaders/ColorFragmentShader.txt");
	rectangleShape->SetG_Vertex_Buffer_Data(
											new float[rectangleShape->GetVertexCount() * 3]
											{
												50.0f,50.0f, 0.0f,
												-50.0f,50.0f, 0.0f,
												50.0f, -50.0f, 0.0f,
												-50.0f, -50.0f,0.0f,
											}
											);
	rectangleShape->SetG_Color_Buffer_Data(
										   new float[rectangleShape->GetVertexCount() * 3]
										   {
												0.344f,0.255f,0.666f,
												0.457f,0.432f,0.645f,
												0.101f,0.846f,0.222f,
												0.333f,0.512f,0.410f,
										   }
										   );
	rectangle->AddComponent(rectangleShape);


	AddChild(triangle);
	triangle->AddChild(sprite);
	sprite->AddChild(rectangle);
}


ScGraphShapeObject::~ScGraphShapeObject()
{
	delete triangle;
	delete sprite;
	delete rectangle;
}
