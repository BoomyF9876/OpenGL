#include "Mesh.h"
#include "Shader.h"
#include "GameController.h"
#include <OBJ_Loader.h>

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
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
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

void Mesh::LoadVec3(json::JSON& jsonData, const char* name, glm::vec3& vec)
{

	json::JSON& data = jsonData[name];
	if (data.hasKey("x")) vec.x = data["x"].ToFloat();
	if (data.hasKey("y")) vec.y = data["y"].ToFloat();
	if (data.hasKey("z")) vec.z = data["z"].ToFloat();

	if (data.hasKey("r")) vec.x = data["r"].ToFloat();
	if (data.hasKey("g")) vec.y = data["g"].ToFloat();
	if (data.hasKey("b")) vec.z = data["b"].ToFloat();
}

void Mesh::LoadObj(const std::string& _filename)
{
	objl::Loader loader;

	M_ASSERT(loader.LoadFile(_filename) == true, "Failed to load mesh");

	for (auto& currentMesh : loader.LoadedMeshes)
	{
		for (auto& vertex : currentMesh.Vertices)
		{
			vertexData.push_back(vertex.Position.X);
			vertexData.push_back(vertex.Position.Y);
			vertexData.push_back(vertex.Position.Z);
			vertexData.push_back(vertex.Normal.X);
			vertexData.push_back(vertex.Normal.Y);
			vertexData.push_back(vertex.Normal.Z);
			vertexData.push_back(vertex.TextureCoordinate.X);
			vertexData.push_back(vertex.TextureCoordinate.Y);
		}
	}

	std::string mapKd = loader.LoadedMaterials[0].map_Kd;
	const size_t lastSlashKdIdx = mapKd.find_last_of("\\/");
	if (std::string::npos != lastSlashKdIdx)
	{
		diffuseMap = "../Assets/Textures/" + mapKd.erase(0, lastSlashKdIdx + 1);
	}

	std::string mapKs = loader.LoadedMaterials[0].map_Ks;
	const size_t lastSlashKsIdx = mapKs.find_last_of("\\/");
	if (std::string::npos != lastSlashKsIdx)
	{
		specularMap = "../Assets/Textures/" + mapKs.erase(0, lastSlashKsIdx + 1);
	}
}

void Mesh::Create(json::JSON& jsonData)
{
	M_ASSERT(jsonData.hasKey("Shader"), "Shader is required.");
	shader = GameController::GetInstance().GetShader(jsonData["Shader"].ToString().c_str());

	if (jsonData.hasKey("Position")) LoadVec3(jsonData, "Position", position);
	if (jsonData.hasKey("Rotation")) LoadVec3(jsonData, "Rotation", rotation);
	if (jsonData.hasKey("Scale")) LoadVec3(jsonData, "Scale", scale);

	if (jsonData.hasKey("LightDirection"))
	{
		LoadVec3(jsonData, "LightDirection", lightDirection);
		lightDirection = glm::normalize(lightDirection);
	}
	if (jsonData.hasKey("LightColor")) LoadVec3(jsonData, "LightColor", lightColor);
	if (jsonData.hasKey("AmbientColor")) LoadVec3(jsonData, "AmbientColor", ambientColor);
	if (jsonData.hasKey("SpecularColor")) LoadVec3(jsonData, "SpecularColor", specularColor);
	if (jsonData.hasKey("SpecularStrength")) specularStrength = jsonData["SpecularStrength"].ToFloat();

	if (jsonData.hasKey("PointLightconstant")) pointLightconstant = jsonData["PointLightconstant"].ToFloat();
	if (jsonData.hasKey("PointLightlinear")) pointLightlinear = jsonData["PointLightlinear"].ToFloat();
	if (jsonData.hasKey("PointLightquadratic")) pointLightquadratic = jsonData["PointLightquadratic"].ToFloat();

	if (jsonData.hasKey("SpotLightconeAngle")) spotLightconeAngle = jsonData["SpotLightconeAngle"].ToFloat();
	if (jsonData.hasKey("SpotLightfalloff")) spotLightfalloff = jsonData["SpotLightfalloff"].ToFloat();

	diffuseTexture = new Texture();
	if (jsonData.hasKey("DiffuseTexture"))
	{
		diffuseTexture->LoadTexture(jsonData["DiffuseTexture"].ToString().c_str());
	}
	specularTexture = new Texture();
	if (jsonData.hasKey("SpecularTexture"))
	{
		specularTexture->LoadTexture(jsonData["SpecularTexture"].ToString().c_str());
	}

	M_ASSERT(jsonData.hasKey("Model"), "Model file is required");
	LoadObj(jsonData["Model"].ToString());

	diffuseTexture = new Texture();
	if (diffuseMap.size() > 0)
		diffuseTexture->LoadTexture(diffuseMap.c_str());

	specularTexture = new Texture();
	if (specularMap.size() > 0)
		specularTexture->LoadTexture(specularMap.c_str());

	/*shader = _shader;
	diffuseTexture = new Texture();
	diffuseTexture->LoadTexture("../Assets/Textures/MetalFrameWood.jpg");

	specularTexture = new Texture();
	specularTexture->LoadTexture("../Assets/Textures/MetalFrame.jpg");*/

	//vertexData = {
	//	/* Position */ /* Normals */ /* Texture Coords */
	//	-1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
	//	1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
	//	1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
	//	1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
	//	-1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
	//	-1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
	//	-1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	//	1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
	//	1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
	//	1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
	//	-1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
	//	-1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	//	-1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	//	-1.0f, 1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
	//	-1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	//	-1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	//	-1.0f, -1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	//	-1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	//	1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	//	1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
	//	1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	//	1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	//	1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	//	1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	//	-1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
	//	1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
	//	1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
	//	1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
	//	-1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
	//	-1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
	//	-1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,

	//	1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
	//	1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	//	1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	//	-1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
	//	-1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
	//};


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

std::string Mesh::Concat(const std::string& _s1, int _index, const std::string& _s2)
{
	std::string index = std::to_string(_index);
	return (_s1 + index + _s2);
}

void Mesh::SetShaderVariables(glm::mat4 _pv, const std::list<Mesh*>& _lights)
{
	shader->SetMat4("World", world);
	shader->SetMat4("WVP", _pv * world);
	shader->SetVec3("CameraPosition", cameraPosition);

	/*shader->SetVec3("light.position", lightposition);
	shader->SetVec3("light.direction", glm::normalize(glm::vec3({0,0,0})-lightposition));
	shader->SetFloat("light.constant", 1.0f);
	shader->SetFloat("light.linear", 0.007f);
	shader->SetFloat("light.quadratic", 0.0002f);
	shader->SetVec3("light.ambientColor", { 0.1f, 0.1f, 0.1f });
	shader->SetVec3("light.diffuseColor", lightColor);
	shader->SetVec3("light.specularColor", { 3.0f, 3.0f, 3.0f });
	shader->SetFloat("light.coneAngle", glm::radians(15.0f));
	shader->SetFloat("light.falloff", 100);*/
	M_ASSERT(_lights.size() <= 4, "Diffuse Shader only supports 4 lights");
	shader->SetInt("numLights", (int)_lights.size());
	int i = 0;
	for (auto& light : _lights) {
		shader->SetVec3(Concat("light[", i, "].position").c_str(), light->GetPosition());
		shader->SetVec3(Concat("light[", i, "].direction").c_str(), light->GetLightDirection());

		shader->SetVec3(Concat("light[", i, "].ambientColor").c_str(), light->GetAmbientColor());
		shader->SetVec3(Concat("light[", i, "].diffuseColor").c_str(), light->GetLightColor());
		shader->SetVec3(Concat("light[", i, "].specularColor").c_str(), light->GetSpecularColor());

		shader->SetFloat(Concat("light[", i, "].constant").c_str(), light->GetPointLightConstant());
		shader->SetFloat(Concat("light[", i, "].linear").c_str(), light->GetPointLightLinear());
		shader->SetFloat(Concat("light[", i, "].quadratic").c_str(), light->GetPointLightQuadratic());

		shader->SetFloat(Concat("light[", i, "].coneAngle").c_str(), glm::radians(light->GetConeAngle()));
		shader->SetFloat(Concat("light[", i, "].falloff").c_str(), light->GetFalloff());
		i++;
	}
	shader->SetFloat("material.specularStrength", specularStrength);
	shader->SetTextureSampler("material.diffuseTexture", GL_TEXTURE0, 0, diffuseTexture->GetTexture());
	shader->SetTextureSampler("material.specularTexture", GL_TEXTURE1, 1, specularTexture->GetTexture());

}

void Mesh::Render(glm::mat4 _pv, const std::list<Mesh*>& _lights)
{
	glUseProgram(shader->GetProgramID());
	CalculateTransform();
	SetShaderVariables(_pv, _lights);
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
