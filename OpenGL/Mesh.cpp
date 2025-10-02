#include "Mesh.h"

Mesh::~Mesh()
{
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &indexBuffer);
	delete texture1;
	delete texture2;
}

void Mesh::Create(Shader* _shader)
{
	shader = _shader;

	texture1 = new Texture();
	texture1->LoadTexture("../Assets/Textures/Tacos.jpg");

	texture2 = new Texture();
	texture2->LoadTexture("../Assets/Textures/Pattern.png");

	

	vertexData = {
		50.0f, 50.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		50.0f, -50.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		-50.0f, -50.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		-50.0f, 50.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	};
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), vertexData.data(), GL_STATIC_DRAW);

	indexData = {
		2,0,3,2,1,0
	};

	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexData.size() * sizeof(float), indexData.data(), GL_STATIC_DRAW);

}

void Mesh::Render(glm::mat4 _wvp)
{
	glUseProgram(shader->GetProgramID());//Use our shader

	//world = glm::rotate(world, 0.01f, { 0,1,0 });
	_wvp *= world;
	glUniformMatrix4fv(shader->GetAttrWVP(), 1, FALSE, &_wvp[0][0]);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

	glEnableVertexAttribArray(shader->GetAttrVertices());
	glVertexAttribPointer(
		shader->GetAttrVertices(), // The attribute we want to configure
		3,                          // size
		GL_FLOAT,                   // type
		GL_FALSE,                   // normalized?
		8*sizeof(float),                          // stride
		(void*)0                    // array buffer offset
	);

	glEnableVertexAttribArray(shader->GetAttrColor());
	glVertexAttribPointer(
		shader->GetAttrColor(), // The attribute we want to configure
		3,                          // size
		GL_FLOAT,                   // type
		GL_FALSE,                   // normalized?
		8 * sizeof(float),                          // stride
		(void*)(3 * sizeof(float))                    // array buffer offset
	);

	glEnableVertexAttribArray(shader->GetAttrTexCoords());
	glVertexAttribPointer(
		shader->GetAttrTexCoords(), // The attribute we want to configure
		2,                          // size
		GL_FLOAT,                   // type
		GL_FALSE,                   // normalized?
		8 * sizeof(float),                          // stride
		(void*)(6 * sizeof(float))                    // array buffer offset
	);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1->GetTexture());
	glUniform1i(shader->GetTexSampler1(), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2->GetTexture());
	glUniform1i(shader->GetTexSampler2(), 1);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glDrawElements(GL_TRIANGLES, indexData.size(), GL_UNSIGNED_INT, (void*)0);

	glDisableVertexAttribArray(shader->GetAttrVertices());
	glDisableVertexAttribArray(shader->GetAttrColor());
	glDisableVertexAttribArray(shader->GetAttrTexCoords());
}