#include "ShapeComponent.h"



ShapeComponent::ShapeComponent()
{
	componentType = ShapeType;

	g_vertex_buffer_data = nullptr;
	g_color_buffer_data = nullptr;
	g_uv_buffer_data = nullptr;
}

void ShapeComponent::Start(const char * componentName, Renderer * rendererPtr, int vertexCountValue, glm::mat4 * modelRef)
{
	Component::Start(componentName);
	renderer = rendererPtr;
	model = modelRef;
	vertexCount = vertexCountValue;
}

int & ShapeComponent::GetVertexCount()
{
	return vertexCount;
}

void ShapeComponent::SetG_Vertex_Buffer_Data(float * g_vertex_buffer_data_Ptr)
{
	g_vertex_buffer_data = g_vertex_buffer_data_Ptr;
	vertexBuffer = renderer->GenBuffer(sizeof(float) * vertexCount * 3, g_vertex_buffer_data);
}

void ShapeComponent::SetG_Color_Buffer_Data(float * g_color_buffer_data_Ptr)
{
	g_color_buffer_data = g_color_buffer_data_Ptr;
	colorBuffer = renderer->GenColorBuffer(sizeof(float) * vertexCount * 3, g_color_buffer_data);
}

void ShapeComponent::SetG_UV_Buffer_Data(float * g_uv_buffer_data_Ptr)
{
	g_uv_buffer_data = g_uv_buffer_data_Ptr;
	uvBuffer = renderer->GenUVBuffer(sizeof(float) * vertexCount * 2, g_uv_buffer_data);
}

void ShapeComponent::Update()
{
	Component::Update();
}

void ShapeComponent::SetMaterial(const char * vertexShader, const char * fragmentShader)
{
	material = Material::CreateMaterial(vertexShader, fragmentShader);
}

Material * ShapeComponent::GetMaterial()
{
	return material;
}

void ShapeComponent::Draw()
{
	renderer->LoadIdentityMatrix();
	renderer->SetModelMatrix(*model);

	if (material != nullptr)
	{
		material->Bind();
		material->SetMatrixProperty(renderer->GetMVP());
		if (g_uv_buffer_data != nullptr)
		{
			material->SetTextureProperty();
		}
	}

	renderer->EnableAttributes(0);
	renderer->BindBuffer(vertexBuffer, 0);

	if (g_uv_buffer_data != nullptr)
	{
		renderer->EnableAttributes(1);
		renderer->BindBuffer(uvBuffer, 0);
		g_color_buffer_data = nullptr;
	}
	else if (g_color_buffer_data != nullptr)
	{
		renderer->EnableAttributes(1);
		renderer->BindBuffer(colorBuffer, 0);
		g_uv_buffer_data = nullptr;
	}

	renderer->DrawBuffer(vertexCount);

	renderer->DisableAttributes(0);
	if (g_color_buffer_data != nullptr || g_uv_buffer_data != nullptr)
	{
		renderer->DisableAttributes(1);
	}

	cout << *g_vertex_buffer_data << endl;
	cout << vertexBuffer << endl;
}

ShapeComponent::~ShapeComponent()
{
	if (g_vertex_buffer_data != nullptr)
	{
		renderer->DestroyBuffer(vertexBuffer);
		delete[] g_vertex_buffer_data;
	}
	if (g_color_buffer_data != nullptr)
	{
		renderer->DestroyBuffer(colorBuffer);
		delete[] g_color_buffer_data;
	}
	if (g_uv_buffer_data != nullptr)
	{
		renderer->DestroyBuffer(uvBuffer);
		delete[] g_uv_buffer_data;
	}
}