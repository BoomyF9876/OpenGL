#include "Mesh.h"

Mesh::~Mesh()
{
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &indexBuffer);
}

void Mesh::Create(Shader* _shader)
{
	shader = _shader;
#pragma region Icosahedron Vertix Data
	float a = 26.0f;
	float b = 42.0f;
	
	vertexData = {
		-a, 0.0f, b,  1.0f, 0.0f, 0.0f, 1.0f,
		a, 0.0f, b,  1.0f, 0.549f, 0.0f, 1.0f,
		-a, 0.0f, -b,  1.0f, 1.0f, 0.0f, 1.0f,
		a, 0.0f,-b,  1.0f, 1.0f, 0.0f, 1.0f,
		0.0f, b, a,  0.0f, 0.0f,1.0f, 1.0f,
		0.0f, b, -a, 0.294f, 0.0f, 0.51f, 1.0f,
		0.0f, -b, a, 0.502f, 0.0f, 0.502f, 1.0f,
		0.0f, -b, -a, 1.0f, 1.0f, 1.0f, 1.0f,
		b, a, 0.0f,   0.0f, 1.0f, 1.0f, 1.0f,
		-b, a, 0.0f,  0.0f, 0.0f,0.0f, 1.0f,
		b, -a, 0.0f,  0.118f, 0.565f, 1.0f, 1.0f,
		-b, -a, 0.0f, 0.863f, 0.078f ,0.235f, 1.0f
	};
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), vertexData.data(), GL_STATIC_DRAW);

#pragma region Icosahedron Index Data
	indexData = {
		0,6,1,0,11,6,1,4,0,1,8,4,
		1,10,8,2,5,3,2,9,5,2,11,9,
		3,7,2,3,10,7,4,8,5,4,9,0,
		5,8,3,5,9,4,6,10,1,6,11,7,
		7,10,6,7,11,2,8,10,3,9,11,0
	};

#pragma endregion
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexData.size() * sizeof(GLuint), indexData.data(), GL_STATIC_DRAW);
}

void Mesh::Render(glm::mat4 _wvp)
{
	glUseProgram(shader->GetProgramID());//Use our shader

	world = glm::rotate(world, glm::radians(0.1f), glm::vec3(0, 1, 0));

	//1st attribute buffer : vertices
	glEnableVertexAttribArray(shader->GetAttrVertices());
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	_wvp *= world;
	glUniformMatrix4fv(shader->GetAttrWVP(), 1, FALSE, &_wvp[0][0]);
	glVertexAttribPointer(
		shader->GetAttrVertices(), // The attribute we want to configure
		3,                          // size
		GL_FLOAT,                   // type
		GL_FALSE,                   // normalized?
		7*sizeof(float),                          // stride
		(void*)0                    // array buffer offset
	);

	glEnableVertexAttribArray(shader->GetAttrColor());
	glVertexAttribPointer(
		shader->GetAttrColor(), // The attribute we want to configure
		4,                          // size
		GL_FLOAT,                   // type
		GL_FALSE,                   // normalized?
		7 * sizeof(float),                          // stride
		(void*)(3 * sizeof(float))                    // array buffer offset
	);

	//Draw the triangle !
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glDrawElements(GL_TRIANGLES, indexData.size(), GL_UNSIGNED_INT, (void*)0);	
	glDisableVertexAttribArray(shader->GetAttrVertices());
	glDisableVertexAttribArray(shader->GetAttrColor());
}