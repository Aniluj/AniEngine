#pragma once

#include "Component.h"
#include "Exports.h"
#include "Material.h"
#include "Renderer.h"

class ENGINEDLL_API ShapeComponent : public Component
{
private:
	unsigned int vertexBuffer;
	unsigned int colorBuffer;
	unsigned int uvBuffer;

	float * g_vertex_buffer_data;
	float * g_color_buffer_data;
	float * g_uv_buffer_data;

	int vertexCount;

	Material * material;
	Renderer * renderer;
	glm::mat4 * model;
public:
	ShapeComponent();

	void Start(const char * componentName, Renderer * rendererPtr, int vertexCountValue, glm::mat4 * modelRef);
	void Draw() override;
	void Update() override;

	void SetMaterial(const char * vertexShaderPath, const char * fragmentShaderPath);
	Material * GetMaterial();

	int & GetVertexCount();
	void SetG_Vertex_Buffer_Data(float * g_vertex_buffer_data_Ptr);
	void SetG_Color_Buffer_Data(float * g_color_buffer_data_Ptr);
	void SetG_UV_Buffer_Data(float * g_uv_buffer_data_Ptr);
	float *& GetG_UV_Buffer_Data();
	unsigned int & GetUVBuffer();

	~ShapeComponent();
};

