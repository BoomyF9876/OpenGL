#include "Mesh.h"

Mesh::~Mesh()
{
	glDeleteBuffers(1, &vertexBuffer);
}

void Mesh::Create(Shader* _shader)
{
	shader = _shader;
	vertexData = { -1.0f,-1.0f,0.0f,
		1.0f,-1.0f,0.0f,
		0.0f,1.0f,0.0f };
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), vertexData.data(), GL_STATIC_DRAW);
}

void Mesh::Render()
{
	glUseProgram(shader->GetProgramID());//Use our shader

	//1st attribute buffer : vertices
	glEnableVertexAttribArray(shader->GetAttrVertices());
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(
		shader->GetAttrVertices(), // The attribute we want to configure
		3,                          // size
		GL_FLOAT,                   // type
		GL_FALSE,                   // normalized?
		0,                          // stride
		(void*)0                    // array buffer offset
	);
	glDrawArrays(GL_TRIANGLES, 0, vertexData.size() / 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
	glDisableVertexAttribArray(shader->GetAttrVertices());
}