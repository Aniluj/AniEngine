#include "Transform.h"


Transform::Transform()
{

}

void Transform::Start(const char * componentName)
{
	this->componentName = componentName;
	componentType = TransformType;
	localPosition = glm::vec3(0.0f);
	localRotation = glm::vec3(0.0f);
	localScale = glm::vec3(1.0f);
	//worldPosition = glm::vec3(0.0f);
	model = glm::mat4(1.0f);
	translationMatrix = glm::mat4(1.0f);
	rotationX = glm::mat4(1.0f);
	rotationY = glm::mat4(1.0f);
	rotationZ = glm::mat4(1.0f);
	scallingMatrix = glm::mat4(1.0f);
}

void Transform::UpdateModel()
{
	model = translationMatrix * (rotationX * rotationY * rotationZ) * scallingMatrix;

	/*cout << "x1:  " << model[0][0] << endl;
	cout << "y1:  " << model[0][1] << endl;
	cout << "z1:  " << model[0][2] << endl;

	cout << "x2:  " << model[1][0] << endl;
	cout << "y2:  " << model[1][1] << endl;
	cout << "z2:  " << model[1][2] << endl;

	cout << "x3:  " << model[2][0] << endl;
	cout << "y3:  " << model[2][1] << endl;
	cout << "z3:  " << model[2][2] << endl;*/
}

glm::mat4& Transform::GetModel()
{
	return model;
}

void Transform::Translate(float x, float y, float z)
{
	glm::vec3 vector3(x, y, z);

	localPosition = vector3;

	translationMatrix = glm::translate(glm::mat4(1.0f), vector3);
	
	/*cout << "x1:  " << translationMatrix[0][0] << endl;
	cout << "y1:  " << translationMatrix[0][1] << endl;
	cout << "z1:  " << translationMatrix[0][2] << endl;
	
	cout << "x2:  " << translationMatrix[1][0] << endl;
	cout << "y2:  " << translationMatrix[1][1] << endl;
	cout << "z2:  " << translationMatrix[1][2] << endl;
	
	cout << "x3:  " << translationMatrix[2][0] << endl;
	cout << "y3:  " << translationMatrix[2][1] << endl;
	cout << "z3:  " << translationMatrix[2][2] << endl;*/

	UpdateModel();
}

void Transform::Scale(float x, float y, float z)
{
	glm::vec3 vector3(x, y, z);

	scallingMatrix = glm::scale(vector3);

	UpdateModel();
}

void Transform::RotateX(float angle)
{
	glm::vec3 vectorAxis;

	vectorAxis[0] = 1.0f;
	vectorAxis[1] = 0.0f;
	vectorAxis[2] = 0.0f;

	rotationX = glm::rotate(glm::mat4(1.0f), glm::radians(angle), vectorAxis);

	UpdateModel();
}

void Transform::RotateY(float angle)
{
	glm::vec3 vectorAxis;

	vectorAxis[0] = 0.0f;
	vectorAxis[1] = 1.0f;
	vectorAxis[2] = 0.0f;

	rotationY = glm::rotate(glm::mat4(1.0f), glm::radians(angle), vectorAxis);

	UpdateModel();
}

void Transform::RotateZ(float angle)
{
	glm::vec3 vectorAxis;

	vectorAxis[0] = 0.0f;
	vectorAxis[1] = 0.0f;
	vectorAxis[2] = 1.0f;

	rotationZ = glm::rotate(glm::mat4(1.0f), glm::radians(angle), vectorAxis);

	UpdateModel();
}

void Transform::Update()
{
	Component::Update();
}

void Transform::Draw()
{
	Component::Draw();
}

Transform::~Transform()
{
}

