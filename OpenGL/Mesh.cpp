#include "Mesh.h"

Mesh::~Mesh()
{
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &indexBuffer);
	delete diffuseTexture;
	delete specularTexture;
}
void Mesh::BindAttributes()
{
	//glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	#pragma region Set Vertices
	glEnableVertexAttribArray(shader->GetAttrVertices());
	glVertexAttribPointer(
		shader->GetAttrVertices(), // The attribute we want to configure
		3,                          // size
		GL_FLOAT,                   // type
		GL_FALSE,                   // normalized?
		8 * sizeof(float),                          // stride
		(void*)0                    // array buffer offset
	);
	
	#pragma endregion
	
#pragma region Set Normals
	glEnableVertexAttribArray(shader->GetAttrNormals());
	glVertexAttribPointer(
		shader->GetAttrNormals(), // The attribute we want to configure
		3,                          // size
		GL_FLOAT,                   // type
		GL_FALSE,                   // normalized?
		8 * sizeof(float),                          // stride
		(void*)(3 * sizeof(float))                    // array buffer offset
	);
#pragma endregion

#pragma region Set Texture Coordinates
	glEnableVertexAttribArray(shader->GetAttrTexCoords());
	glVertexAttribPointer(
		shader->GetAttrTexCoords(), // The attribute we want to configure
		2,                          // size
		GL_FLOAT,                   // type
		GL_FALSE,                   // normalized?
		8 * sizeof(float),                          // stride
		(void*)(6 * sizeof(float))                    // array buffer offset
	);
#pragma endregion

#pragma region Set Texture 0
	/*glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1->GetTexture());
	glUniform1i(shader->GetTexSampler1(), 0);*/
#pragma endregion

#pragma region Set Texture 1
	//glActiveTexture(GL_TEXTURE1);
	//glBindTexture(GL_TEXTURE_2D, texture2->GetTexture());
	//glUniform1i(shader->GetTexSampler2(), 1);
#pragma endregion
}

void Mesh::Create(Shader* _shader)
{
	shader = _shader;
	diffuseTexture = new Texture();
	diffuseTexture->LoadTexture("../Assets/Textures/MetalFrameWood.jpg");

	specularTexture = new Texture();
	specularTexture->LoadTexture("../Assets/Textures/MetalFrame.jpg");

	vertexData = {/* Position */ /* Normals */ /* Texture
Coords */
-50.0f, -50.0f, -50.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
50.0f, -50.0f, -50.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
50.0f, 50.0f, -50.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
50.0f, 50.0f, -50.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
-50.0f, 50.0f, -50.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
-50.0f, -50.0f, -50.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
-50.0f, -50.0f, 50.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
50.0f, -50.0f, 50.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
50.0f, 50.0f, 50.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
50.0f, 50.0f, 50.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
-50.0f, 50.0f, 50.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
-50.0f, -50.0f, 50.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
-50.0f, 50.0f, 50.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
-50.0f, 50.0f, -50.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
-50.0f, -50.0f, -50.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
-50.0f, -50.0f, -50.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
-50.0f, -50.0f, 50.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
-50.0f, 50.0f, 50.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
50.0f, 50.0f, 50.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
50.0f, 50.0f, -50.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
50.0f, -50.0f, -50.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
50.0f, -50.0f, -50.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
50.0f, -50.0f, 50.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
50.0f, 50.0f, 50.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
-50.0f, -50.0f, -50.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
50.0f, -50.0f, -50.0f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
50.0f, -50.0f, 50.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
50.0f, -50.0f, 50.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
-50.0f, -50.0f, 50.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
-50.0f, -50.0f, -50.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
-50.0f, 50.0f, -50.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
50.0f, 50.0f, -50.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
50.0f, 50.0f, 50.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
50.0f, 50.0f, 50.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
-50.0f, 50.0f, 50.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
-50.0f, 50.0f, -50.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
	};

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), vertexData.data(), GL_STATIC_DRAW);

}

void Mesh::CalculateTransform()
{
	world = glm::translate(glm::mat4(1.0f), position);
	world = glm::rotate(world, rotation.x, glm::vec3(1, 0, 0));
	world = glm::rotate(world, rotation.y, glm::vec3(0, 1, 0));
	world = glm::rotate(world, rotation.z, glm::vec3(0, 0, 1));
	world = glm::scale(world, scale);
}

void Mesh::SetShaderVariables(glm::mat4 _pv)
{
	shader->SetMat4("World", world);
	shader->SetMat4("WVP", _pv * world);
	shader->SetVec3("CameraPosition", cameraPosition);

	shader->SetVec3("light.position", lightposition);
	shader->SetVec3("light.color", lightcolor);
	shader->SetVec3("light.ambientColor", { 0.1f, 0.1f, 0.1f });
	shader->SetVec3("light.diffuseColor", { 1.0f, 1.01f, 1.0f });
	shader->SetVec3("light.specularColor", { 3.0f, 3.0f, 3.0f });

	shader->SetFloat("material.specularStrength", 8);
	shader->SetTextureSampler("material.diffuseTexture", GL_TEXTURE0, 0, diffuseTexture->GetTexture());
	shader->SetTextureSampler("material.specularTexture", GL_TEXTURE1, 1, specularTexture->GetTexture());

}

void Mesh::Render(glm::mat4 _pv)
{
	glUseProgram(shader->GetProgramID());
	CalculateTransform();
	SetShaderVariables(_pv);
	BindAttributes();

	if (!indexData.empty()) {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
		glDrawElements(GL_TRIANGLES, (GLsizei)indexData.size(), GL_UNSIGNED_INT, (void*)0);
	}
	else {
		glDrawArrays(GL_TRIANGLES, 0, (GLsizei)(vertexData.size() / 8));
	}

	glDisableVertexAttribArray(shader->GetAttrVertices());
	glDisableVertexAttribArray(shader->GetAttrNormals());
	glDisableVertexAttribArray(shader->GetAttrTexCoords());
}
