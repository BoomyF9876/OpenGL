#include "Mesh.h"

Mesh::~Mesh()
{
	glDeleteBuffers(1, &vertexBuffer);
}

void Mesh::Create(Shader* _shader)
{
	shader = _shader;
	vertexData = {
		// Triangle 1 (▲)
		0.0f,  0.5f, 0.0f,   1.0f,0.0f,0.0f,1.0f, // Vertex 1: 左上
		1.0f,  0.5f, 0.0f,   0.0f,1.0f,0.0f,1.0f, // Vertex 2: 右上*
		0.0f, -0.5f, 0.0f,   0.0f,0.0f,1.0f,1.0f, // Vertex 3: 左下*

		// Triangle 2 (▼)
		0.0f, -0.5f, 0.0f,   1.0f,0.0f,0.0f,1.0f, // Vertex 4: 左下*
		1.0f,  0.5f, 0.0f,   0.0f,1.0f,0.0f,1.0f, // Vertex 5: 右上*
		1.0f, -0.5f, 0.0f,   0.0f,0.0f,1.0f,1.0f, // Vertex 6: 右下

		// Triangle 3 (▲)
		1.0f,  0.5f, 0.0f,   1.0f,0.0f,0.0f,1.0f, // Vertex 7: 左上*
		2.0f,  0.5f, 0.0f,   0.0f,1.0f,0.0f,1.0f, // Vertex 8: 右上
		1.0f, -0.5f, 0.0f,   0.0f,0.0f,1.0f,1.0f, // Vertex 9: 左下*

		// Triangle 4 (▼)
		1.0f, -0.5f, 0.0f,   1.0f,0.0f,0.0f,1.0f, // Vertex 10: 左下*
		2.0f,  0.5f, 0.0f,   0.0f,1.0f,0.0f,1.0f, // Vertex 11: 右上*
		2.0f, -0.5f, 0.0f,   0.0f,0.0f,1.0f,1.0f, // Vertex 12: 右下

		// Triangle 5 (▲)
		2.0f,  0.5f, 0.0f,   1.0f,0.0f,0.0f,1.0f, // Vertex 13: 左上*
		3.0f,  0.5f, 0.0f,   0.0f,1.0f,0.0f,1.0f, // Vertex 14: 右上
		2.0f, -0.5f, 0.0f,   0.0f,0.0f,1.0f,1.0f  // Vertex 15: 左下*
	};
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), vertexData.data(), GL_STATIC_DRAW);
}

void Mesh::Render(glm::mat4 _wvp)
{
	glUseProgram(shader->GetProgramID());//Use our shader

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
	glDrawArrays(GL_TRIANGLES, 0, vertexData.size() / 7); // Starting from vertex 0; 3 vertices total -> 1 triangle
	glDisableVertexAttribArray(shader->GetAttrVertices());
	glDisableVertexAttribArray(shader->GetAttrColor());
}