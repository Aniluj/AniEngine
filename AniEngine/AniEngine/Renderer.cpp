#include "Renderer.h"
#include <glew.h>
#include "GLFW\glfw3.h"
#include "BSP.h"
#include "Node.h"



Renderer::Renderer()
{
}


Renderer::~Renderer()
{
	glDeleteVertexArrays(1, &vertexArrayID);
	//delete frustumPlanes;
}

bool Renderer::Start(Window* windowPtr)
{
	if (windowPtr != nullptr)
	{
		window = windowPtr;

		glfwMakeContextCurrent((GLFWwindow*)window->GetWindowPtr());

		if(glewInit()!=GLEW_OK)
		{
			return false;
		}

		glGenVertexArrays(1, &vertexArrayID);
		glBindVertexArray(vertexArrayID);
		
		//frustumPlanes = new vector<Plane*>();

		//frustumPlanes = new Plane[6];

		//SetProjectionMatrixToOrtho(0.0f, (float)window->GetWidth(), 0.0f, (float)window->GetHeight(), 0.1f, 1000.0f);
		//SetViewMatrix(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

		/*viewMatrix = glm::lookAt(
			glm::vec3(0, 0, 3), 
			glm::vec3(0, 0, 0), 
			glm::vec3(0, 1, 0)  
		);*/

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		cout << "Renderer::Start()" << endl;
		
		LoadIdentityMatrix();

		return true;
	}

	return false;
}

void Renderer::SetViewMatrix(glm::vec3 eye, glm::vec3 center, glm::vec3 up)
{
	viewMatrix = glm::lookAt(eye, center, up);
}

void Renderer::SetViewMatrix(glm::mat4 viewMatrixValues)
{
	viewMatrix = viewMatrixValues;
}

void Renderer::SetProjectionMatrixToOrtho(float left, float right, float bottom, float top, float zNear, float zFar)
{
	projectionMatrix = glm::ortho(left, right, bottom, top, zNear, zFar);
	typeOfProjection = Ortho;
}

void Renderer::SetProjectionMatrixToOrtho(float left, float right, float bottom, float top)
{
	projectionMatrix = glm::ortho(left, right, bottom, top);
	typeOfProjection = Ortho;
}

void Renderer::SetProjectionMatrixToPerspective(float fovy, float aspect, float zNear, float zFar)
{
	projectionMatrix = glm::perspective(fovy, aspect, zNear, zFar);
	typeOfProjection = Perspective;
}


bool Renderer::Stop()
{
	cout << "Renderer::Stop()" << endl;

	return true;
}

void Renderer::ClearColor(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
}

void Renderer::ClearScreen()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::SwapBuffer()
{
	glfwSwapBuffers((GLFWwindow*)window->GetWindowPtr());
}

unsigned int Renderer::GenBuffer(unsigned int size,float * g_vertex_buffer_data)
{

	GLuint vertexbuffer;

	glGenBuffers(1, &vertexbuffer);

	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

	glBufferData(GL_ARRAY_BUFFER, size, g_vertex_buffer_data, GL_STATIC_DRAW);

	return vertexbuffer;
}

unsigned int Renderer::GenElementBuffer(unsigned int size, const void * g_element_buffer_data)
{
	GLuint elementbuffer;

	glGenBuffers(1, &elementbuffer);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, g_element_buffer_data, GL_STATIC_DRAW);

	return elementbuffer;
}

void Renderer::DrawBuffer(int vertexCount)
{
	glDrawArrays(GL_TRIANGLE_STRIP, 0, vertexCount);
}

void Renderer::DrawElementBuffer(int vertexCount)
{
	glDrawElements(
		GL_TRIANGLES,      // mode
		vertexCount,    // count
		GL_UNSIGNED_INT,   // type
		(void*)0           // element array buffer offset
	);
}

void Renderer::DestroyBuffer(unsigned int buffer)
{
	glDeleteBuffers(1, &buffer);
}

void Renderer::EnableAttributes(unsigned int attributebID)
{
	glEnableVertexAttribArray(attributebID);
}

void Renderer::BindBuffer(unsigned int vertexBuffer, unsigned int attributebID)
{
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(
		attributebID,       
		3,                  
		GL_FLOAT,           
		GL_FALSE,           
		0,                  
		(void*)0            
	);
}

void Renderer::BindElementBuffer(unsigned int elementBuffer)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
}

void Renderer::NormalVertexAttrib(unsigned int attributebID)
{
	glVertexAttribPointer(
		attributebID,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);
}

void Renderer::BindColorBuffer(unsigned int colorBuffer, unsigned int attributebID)
{
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);

	glVertexAttribPointer(
		attributebID,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);
}

void Renderer::BindUVBuffer(unsigned int uvBuffer, unsigned int attributebID)
{
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glVertexAttribPointer(
		attributebID,                     // attribute. No particular reason for 1, but must match the layout in the shader.
		2,                                // size : U+V => 2
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);
}

void Renderer::BindTexture(unsigned int textureID)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
}

unsigned int Renderer::GenColorBuffer(unsigned int size, float * g_color_buffer_data)
{
	GLuint colorbuffer;

	glGenBuffers(1, &colorbuffer);

	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);

	glBufferData(GL_ARRAY_BUFFER, size, g_color_buffer_data, GL_STATIC_DRAW);

	return colorbuffer;
}

unsigned int Renderer::GenUVBuffer(unsigned int size, float * g_uv_buffer_data)
{
	GLuint uvbuffer;

	glGenBuffers(1, &uvbuffer);

	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);

	glBufferData(GL_ARRAY_BUFFER, size, g_uv_buffer_data, GL_STATIC_DRAW);

	return uvbuffer;
}

void Renderer::DisableAttributes(unsigned int attributeID)
{
	glDisableVertexAttribArray(attributeID);
}

void Renderer::LoadIdentityMatrix()
{
	modelMatrix = glm::mat4(1.0f);

	SetMVP();
}

void Renderer::SetModelMatrix(glm::mat4 model)
{
	modelMatrix = model;

	SetMVP();
}

void Renderer::SetMVP()
{
	MVP = projectionMatrix * viewMatrix * modelMatrix;
}

//void Renderer::NormalizePlanes(Plane & plane)
//{
//	float mag;
//
//	mag = sqrt(plane.a * plane.a + plane.b * plane.b + plane.c * plane.c);
//
//	plane.a = plane.a / mag;
//	plane.b = plane.b / mag;
//	plane.c = plane.c / mag;
//	plane.d = plane.d / mag;
//}

glm::vec4 Renderer::CreatePlane(const glm::vec3& normal, const glm::vec3& point)
{
	glm::vec4 plane;

	plane.x = normal.x;
	plane.y = normal.y;
	plane.z = normal.z;
	plane.w = -dot(normal, point);

	return plane;
}
void Renderer::SetFrustumPlanes(glm::vec3 globalPos, glm::vec3 forward, glm::vec3 right, glm::vec3 up, float zNear, float zFar, float aspRatio, float fovy)
{
	glm::vec3 nearCenter = globalPos + forward * zNear;
	glm::vec3 farCenter = globalPos + forward * zFar;

	float fovTan = tan(fovy);

	float nHeight = zNear * fovTan;
	float nWidth = nHeight * aspRatio;

	glm::vec3 leftPlaneVec = (nearCenter + right * nWidth  * 0.5f) - globalPos;
	glm::vec3 rightPlaneVec = (nearCenter - right * nWidth  * 0.5f) - globalPos;
	glm::vec3 topPlaneVec = (nearCenter + up * nHeight * 0.5f) - globalPos;
	glm::vec3 bottomPlaneVec = (nearCenter - up * nHeight * 0.5f) - globalPos;

	glm::vec3 normalLeft = normalize(cross(leftPlaneVec, up));
	glm::vec3 normalRight = -normalize(cross(rightPlaneVec, up));
	glm::vec3 normalTop = -normalize(cross(topPlaneVec, right));
	glm::vec3 normalBottom = normalize(cross(bottomPlaneVec, right));

	planes[(int)Planes::NEAR] = CreatePlane(forward, nearCenter);
	planes[(int)Planes::FAR] = CreatePlane(-forward, farCenter);
	planes[(int)Planes::LEFT] = CreatePlane(normalLeft, globalPos);
	planes[(int)Planes::RIGHT] = CreatePlane(normalRight, globalPos);
	planes[(int)Planes::TOP] = CreatePlane(normalTop, globalPos);
	planes[(int)Planes::BOTTOM] = CreatePlane(normalBottom, globalPos);
}


//void Renderer::SetFrustumPlanes()
//{
//	MultiplyViewAndProjection();
//
//	//Left Clipping Plane
//	frustumPlanes[0].a = combinedViewAndProjectionMatrix[3][0] + combinedViewAndProjectionMatrix[0][0];
//	frustumPlanes[0].b = combinedViewAndProjectionMatrix[3][1] + combinedViewAndProjectionMatrix[0][1];
//	frustumPlanes[0].c = combinedViewAndProjectionMatrix[3][2] + combinedViewAndProjectionMatrix[0][2];
//	frustumPlanes[0].d = combinedViewAndProjectionMatrix[3][3] + combinedViewAndProjectionMatrix[0][3];
//
//
//	//Right Clipping Plane
//	frustumPlanes[1].a = combinedViewAndProjectionMatrix[3][0] - combinedViewAndProjectionMatrix[0][0];
//	frustumPlanes[1].b = combinedViewAndProjectionMatrix[3][1] - combinedViewAndProjectionMatrix[0][1];
//	frustumPlanes[1].c = combinedViewAndProjectionMatrix[3][2] - combinedViewAndProjectionMatrix[0][2];
//	frustumPlanes[1].d = combinedViewAndProjectionMatrix[3][3] - combinedViewAndProjectionMatrix[0][3];
//
//
//	//Top Clipping Plane
//	frustumPlanes[2].a = combinedViewAndProjectionMatrix[3][0] - combinedViewAndProjectionMatrix[1][0];
//	frustumPlanes[2].b = combinedViewAndProjectionMatrix[3][1] - combinedViewAndProjectionMatrix[1][1];
//	frustumPlanes[2].c = combinedViewAndProjectionMatrix[3][2] - combinedViewAndProjectionMatrix[1][2];
//	frustumPlanes[2].d = combinedViewAndProjectionMatrix[3][3] - combinedViewAndProjectionMatrix[1][3];
//
//
//	//Bottom Clipping Plane
//	frustumPlanes[3].a = combinedViewAndProjectionMatrix[3][0] + combinedViewAndProjectionMatrix[1][0];
//	frustumPlanes[3].b = combinedViewAndProjectionMatrix[3][1] + combinedViewAndProjectionMatrix[1][1];
//	frustumPlanes[3].c = combinedViewAndProjectionMatrix[3][2] + combinedViewAndProjectionMatrix[1][2];
//	frustumPlanes[3].d = combinedViewAndProjectionMatrix[3][3] + combinedViewAndProjectionMatrix[1][3];
//
//
//	//Near Clipping Plane
//	frustumPlanes[4].a = combinedViewAndProjectionMatrix[3][0] + combinedViewAndProjectionMatrix[2][0];
//	frustumPlanes[4].b = combinedViewAndProjectionMatrix[3][1] + combinedViewAndProjectionMatrix[2][1];
//	frustumPlanes[4].c = combinedViewAndProjectionMatrix[3][2] + combinedViewAndProjectionMatrix[2][2];
//	frustumPlanes[4].d = combinedViewAndProjectionMatrix[3][3] + combinedViewAndProjectionMatrix[2][3];
//
//
//	//Far Clipping Plane
//	frustumPlanes[5].a = combinedViewAndProjectionMatrix[3][0] - combinedViewAndProjectionMatrix[2][0];
//	frustumPlanes[5].b = combinedViewAndProjectionMatrix[3][1] - combinedViewAndProjectionMatrix[2][1];
//	frustumPlanes[5].c = combinedViewAndProjectionMatrix[3][2] - combinedViewAndProjectionMatrix[2][2];
//	frustumPlanes[5].d = combinedViewAndProjectionMatrix[3][3] - combinedViewAndProjectionMatrix[2][3];
//
//
//
//	//NormalizePlanes(frustumPlanes[0]);
//	//NormalizePlanes(frustumPlanes[1]);
//	//NormalizePlanes(frustumPlanes[2]);
//	//NormalizePlanes(frustumPlanes[3]);
//	//NormalizePlanes(frustumPlanes[4]);
//	//NormalizePlanes(frustumPlanes[5]);
//	
//	//cout << "CHECKEO EN RENDERER " << combinedViewAndProjectionMatrix[3][0] - combinedViewAndProjectionMatrix[0][0] << endl;
//}

void Renderer::NormalizePlane(glm::vec4& plane)
{
	float mag;
	mag = sqrt(plane.x * plane.x + plane.y * plane.y + plane.z * plane.z);
	plane /= mag;
}

Halfspace Renderer::ClassifyPoint(const glm::vec4 & plane, const glm::vec4 & vector)
{
	float distToPlane = plane.x * vector.x + plane.y * vector.y + plane.z * vector.z + plane.w;

	return distToPlane >= 0.0f ? POSITIVE : NEGATIVE;
}

void Renderer::MultiplyModel(glm::mat4 matrix)
{
	modelMatrix *= matrix;

	SetMVP();
}

void Renderer::MultiplyViewAndProjection()
{
	combinedViewAndProjectionMatrix = viewMatrix * projectionMatrix;
}

glm::mat4& Renderer::GetMVP()
{
	return MVP;
}

glm::mat4 Renderer::GetModelMatrix()
{
	return modelMatrix;
}

glm::vec4 * Renderer::GetFrustumPlanesPtr()
{
	return planes;
}

void Renderer::AddBSP(BSP* bsp)
{
	BSPs.push_back(bsp);
}

void Renderer::MakeBSPClean(Node* scene)
{
	for (int i = 0; i < BSPs.size(); i++)
	{
		scene->CheckHalfspace(BSPs[i]);
	}
}