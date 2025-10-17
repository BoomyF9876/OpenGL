#pragma once
#include <vector>
#include <string>
#include <glm/glm.hpp>
#include "Shader.h"
#include "Texture.h"

class Mesh
{
public:
    Mesh() = default;
    ~Mesh();

    void Create(Shader* _shader);
    void LoadFromJSON(const char* jsonPath, Shader* _shader);
    void Render(glm::mat4 _pv);
    void Update(float deltaTime);
    void CalculateTransform();
    void SetShaderVariables(glm::mat4 _pv);
    void BindAttributes();
    void SetRotationRate(float rate) { rotationRate = rate; }
    float GetRotationRate() const { return rotationRate; }
    void SetPosition(glm::vec3 pos) { position = pos; }
    glm::vec3 GetPosition() const { return position; }
    glm::vec3 GetScale() const { return scale; }
    glm::mat4 GetWorld() const { return glm::scale(world, glm::vec3(1) / scale); }

    void SetParent(glm::mat4 _p) { parent = _p; }
    void SetLightPosition(glm::vec3 p) { lightposition = p; }
    void SetLightColor(glm::vec3 c) { lightcolor = c; }
    glm::vec3 GetLightColor() const { return lightcolor; }

private:
    Shader* shader = nullptr;
    Texture* texture1 = nullptr;
    Texture* texture2 = nullptr;

    GLuint vertexBuffer = 0;
    GLuint indexBuffer = 0;

    std::vector<float> vertexData;
    std::vector<GLuint> indexData;

	glm::mat4 parent = glm::mat4(1.0f);
    glm::mat4 world = glm::mat4(1.0f);
    glm::vec3 position = glm::vec3(0.0f);
    glm::vec3 rotation = glm::vec3(0.0f);
    glm::vec3 scale = glm::vec3(1.0f);
    float rotationRate = 0.0f;

    glm::vec3 lightposition = glm::vec3(0.0f);
    glm::vec3 lightcolor = glm::vec3(1.0f);
    glm::vec3 ambientColor = glm::vec3(0.1f);
    glm::vec3 diffuseColor = glm::vec3(1.0f);
    glm::vec3 specularColor = glm::vec3(1.0f);
    float specularStrength = 1.0f;
};