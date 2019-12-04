#include "BSP.h"
#include "Renderer.h"
#include "Camera.h"


BSP::BSP(/*const char* componentName, Renderer * rendererPtr, Camera * gameCamera*/) : material(Material::CreateMaterial("Shaders/TextureTransformVertexShader.txt", "Shaders/TextureFragmentShader.txt")),
																					   position(glm::vec3(100000.0f, 100000.0f, 100000.0f)), forward(glm::vec3(1.0f, 0.0f, 0.0f))
{
	//Start(componentName, rendererPtr, gameCamera,);
}

BSP::~BSP()
{
}

void BSP::Start(const char* componentName, Renderer * rendererPtr, Camera * gameCamera, Transform * transform)
{
	this->componentName = componentName;
	this->gameCamera = gameCamera;
	SetTransform(transform);
	componentType = BSPType;
	//reqTransform = true;
	
	renderer = rendererPtr;

	UpdatePlane();

	renderer->AddBSP(this);
}

void BSP::Update()
{
	if (forward != transform->GetForward())
	{
		forward = transform->GetForward();
		UpdatePlane();
	}

	if (position != transform->GetPosition())
	{
		position = transform->GetPosition();
		UpdatePlane();
	}

	halfspace = renderer->ClassifyPoint(plane, gameCamera->GetCameraPosition());
}

void BSP::Draw()
{
	glm::vec3 right = transform->GetRight();
	glm::vec3 up = transform->GetUp();

	cout << "point right: " << right.x << endl;
	cout << "point up: " << up.y << endl;

	glm::vec3 pointRight = position + right * 25.0f;
	glm::vec3 pointUp = position + up * 25.0f;
																																										

	float* vertex = new float[4 * 3]
	{
		 pointRight.x,  pointUp.y,																																						0,
		-pointRight.x,  pointUp.y,																																						0,
		 pointRight.x, -pointUp.y,																																						0,
		-pointRight.x, -pointUp.y,																																						0,
	};

	vector<unsigned int> indices																																							
	{
		0, 1,																																							
		2, 1,																																							
		2, 3,																																							
	};

	float* verticesColorData = new float[4 * 3]
	{
		0.0f, 0.0f,																																						0.0f,
		0.0f, 0.0f,																																						0.0f,
		0.0f, 0.0f,																																						0.0f,
		0.0f, 0.0f,																																						0.0f,
	};

	if (material != NULL)
	{
		material->Bind();
		renderer->BindTexture(0); //parametro a comparar ante funcionamiento incorrecto
		material->SetMatrixProperty(renderer->GetMVP());
		material->SetTextureProperty();
	}

	renderer->EnableAttributes(0);
	renderer->EnableAttributes(1);

	unsigned int id = renderer->GenBuffer(sizeof(float) * 4 * 3, vertex);
	unsigned int colorId = renderer->GenColorBuffer(sizeof(float) * 4 * 3, verticesColorData);
	unsigned int elementsId = renderer->GenElementBuffer(sizeof(unsigned int) * indices.size(), &indices.at(0));

	renderer->BindBuffer(id, 0);
	renderer->BindColorBuffer(colorId, 1); //funcion a comparar ante funcionamiento incorrecto
	renderer->BindElementBuffer(elementsId);
	renderer->DrawElementBuffer(indices.size()); //funcion a comparar ante funcionamiento incorrecto

	renderer->DisableAttributes(0);
	renderer->DisableAttributes(1);
}

void BSP::SetTransform(Transform* transform)
{
	this->transform = transform;
}

void BSP::UpdatePlane()
{
	plane = renderer->CreatePlane(forward, position);
	renderer->NormalizePlane(plane);
}
