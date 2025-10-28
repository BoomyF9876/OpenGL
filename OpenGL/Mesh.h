#pragma once
#include <vector>
#include <string>
#include <glm/glm.hpp>
#include "Shader.h"
#include "Texture.h"
#include "StandardIncludes.h"

class Mesh
{
public:
    Mesh() = default;
    ~Mesh();

    void Create(Shader* _shader);
    void Render(glm::mat4 _pv);
    void CalculateTransform();
    void SetShaderVariables(glm::mat4 _pv);
    void BindAttributes();
    void SetRotation(glm::vec3 _rotation) { rotation = _rotation; }
    glm::vec3 GetRotation() const { return rotation; }
    void SetPosition(glm::vec3 pos) { position = pos; }
    glm::vec3 GetPosition() const { return position; }
    void SetScale(glm::vec3 _scale) { scale = _scale; }
	void SetCameraPosition(glm::vec3 p) { cameraPosition = p; }

    void SetLightPosition(glm::vec3 p) { lightposition = p; }
    void SetLightColor(glm::vec3 c) { lightcolor = c; }

private:
    Shader* shader = nullptr;
    Texture* diffuseTexture = nullptr;
    Texture* specularTexture = nullptr;

    GLuint vertexBuffer = 0;
    GLuint indexBuffer = 0;

    std::vector<GLfloat> vertexData;
    std::vector<GLubyte> indexData;

    glm::mat4 world = glm::mat4(1.0f);
    glm::vec3 position = { 0.0f, 0.0f, 0.0f };
    glm::vec3 rotation = { 0.0f,0.0f,0.0f };
    glm::vec3 scale = { 1.0f,1.0f, 1.0f };

    glm::vec3 lightposition = glm::vec3(0.0f);
    glm::vec3 lightcolor = glm::vec3(1.0f);
    glm::vec3 cameraPosition = glm::vec3(0.0f);
};