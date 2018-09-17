#pragma once

#include "Exports.h"

class ENGINEDLL_API Material
{
protected:
	unsigned int programID;
public:
	Material();
	~Material();
	static unsigned int LoadShader(const char * vertex_file_path, const char * fragment_file_path);
	void Bind();
	static Material * CreateMaterial(const char * vertex_file_path, const char * fragment_file_path);
};

