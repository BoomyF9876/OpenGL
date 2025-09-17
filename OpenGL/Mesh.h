#pragma once

#ifndef _MESH_H_
#define _MESH_H_

#include "StandardIncludes.h"
#include "Shader.h"

class Mesh
{
public:
	Mesh() = default;
	~Mesh();

	void Create(Shader* _shader);
	void Render();
private:
	Shader* shader = nullptr;
	GLuint vertexBuffer = 0;
	std::vector<GLfloat> vertexData;
};

#endif //!_MESH_H_