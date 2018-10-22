#pragma once

#include "Exports.h"
#include "glm\glm.hpp"

class ENGINEDLL_API Material
{
protected:
	unsigned int programID;
	unsigned int matrixID;
	unsigned int textureID;
public:
	Material();
	~Material();
	static unsigned int LoadShader(const char * vertex_file_path, const char * fragment_file_path);
	void Bind();
	static Material * CreateMaterial(const char * vertex_file_path, const char * fragment_file_path);
	void SetMatrixProperty(glm::mat4& mat);
	void SetTextureProperty(glm::mat4& mat);
};

