#include "Mesh.h"

Mesh::~Mesh()
{
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &indexBuffer);
	delete texture1;
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
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1->GetTexture());
	glUniform1i(shader->GetTexSampler1(), 0);
#pragma endregion

#pragma region Set Texture 1
	//glActiveTexture(GL_TEXTURE1);
	//glBindTexture(GL_TEXTURE_2D, texture2->GetTexture());
	//glUniform1i(shader->GetTexSampler2(), 1);
#pragma endregion
}


void Mesh::CalculateTransform()
{
	world = glm::translate(glm::mat4(1.0f), position);
	world = glm::rotate(world, rotation.x, glm::vec3(1, 0, 0));
	world = glm::rotate(world, rotation.y, glm::vec3(0, 1, 0));
	world = glm::rotate(world, rotation.z, glm::vec3(0, 0, 1));
	world = glm::scale(world, scale);
	world = parent * world;
}

void Mesh::SetShaderVariables(glm::mat4 _pv)
{
	shader->SetMat4("World", world);
	shader->SetVec3("LightPosition", lightposition);
	shader->SetVec3("LightColor", lightcolor);
	shader->SetMat4("WVP", _pv * world);
	shader->SetVec3("AmbientColor", ambientColor);
	shader->SetVec3("DiffuseColor", diffuseColor);
}

void Mesh::LoadFromJSON(const char* jsonPath, Shader* _shader)
{
	shader = _shader;

	json::JSON root = LoadJSON(jsonPath);
	vertexData.clear();
	if (root.hasKey("VertexData")) {
		json::JSON arr = root.at("VertexData");
		for (size_t i = 0; i < arr.size(); ++i)
			vertexData.push_back(static_cast<float>(arr[i].ToFloat()));
	}

	indexData.clear();
	if (root.hasKey("IndexData")) {
		json::JSON arr = root.at("IndexData");
		for (size_t i = 0; i < arr.size(); ++i)
			indexData.push_back(static_cast<GLuint>(arr[i].ToInt()));
	}

	
	if (root.hasKey("LightColor")) {
		auto c = root.at("LightColor");
		lightcolor = { (float)c["r"].ToFloat(), (float)c["g"].ToFloat(), (float)c["b"].ToFloat() };
		int i = 1;
	}
	if (root.hasKey("DiffuseColor")) {
		auto c = root.at("DiffuseColor");
		diffuseColor = { (float)c["r"].ToFloat(), (float)c["g"].ToFloat(), (float)c["b"].ToFloat() };
	}
	if (root.hasKey("AmbientLight")) {
		auto c = root.at("AmbientLight");
		ambientColor = { (float)c["r"].ToFloat(), (float)c["g"].ToFloat(), (float)c["b"].ToFloat() };
	}

	if (root.hasKey("Position")) {
		auto p = root.at("Position");
		position = { (float)p["x"].ToFloat(), (float)p["y"].ToFloat(), (float)p["z"].ToFloat() };
	}
	if (root.hasKey("Scale")) {
		auto s = root.at("Scale");
		scale = { (float)s["x"].ToFloat(), (float)s["y"].ToFloat(), (float)s["z"].ToFloat() };
	}
	if (root.hasKey("RotationRate"))
		rotationRate = (float)root.at("RotationRate").ToFloat();
		//rotation = glm::vec3(0, rotationRate, 0);

	texture1 = new Texture();
	if (root.hasKey("DiffuseTexture")) {
		std::string texPath = root.at("DiffuseTexture").ToString();
		texture1->LoadTexture(texPath.c_str());
	}
	else {
		texture1->LoadTexture("../Assets/Textures/Pattern.png");
	}


	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), vertexData.data(), GL_STATIC_DRAW);

	if (!indexData.empty()) {
		glGenBuffers(1, &indexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexData.size() * sizeof(GLuint), indexData.data(), GL_STATIC_DRAW);
	}
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

void Mesh::Update(float deltaTime)
{
	rotation.y += rotationRate;
}