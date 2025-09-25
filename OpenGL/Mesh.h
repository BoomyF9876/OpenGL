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
	void Render(glm::mat4 _wvp);

	void RotateX(float degrees) 
	{ 
		rotationX += degrees; 
	}

	void RotateY(float degrees) 
	{ 
		rotationY += degrees;
	}

private:
	Shader* shader = nullptr;
	GLuint vertexBuffer = 0;
	GLuint indexBuffer = 0;
	std::vector<GLfloat> vertexData;
	std::vector<GLuint> indexData;
	glm::mat4 world = glm::mat4(1.0f);

	float rotationX = 0.0f;
	float rotationY = 0.0f;
};

#endif //!_MESH_H_