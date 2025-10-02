#pragma once

#ifndef _MESH_H_
#define _MESH_H_

#include "StandardIncludes.h"
#include "Texture.h"
#include "Shader.h"

class Mesh
{
public:
	~Mesh();

	void Create(Shader* _shader);
	void Render(glm::mat4 _wvp);
	
private:
	Shader* shader = nullptr;
	Texture* texture1 = nullptr;
	Texture* texture2 = nullptr;
	GLuint indexBuffer = 0;
	GLuint vertexBuffer = 0;
	std::vector<GLfloat> vertexData;
	std::vector<GLuint> indexData;
	glm::mat4 world = glm::mat4(1);
};

#endif //!_MESH_H_