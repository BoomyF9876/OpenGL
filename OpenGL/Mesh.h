#pragma once

#ifndef _MESH_H_
#define _MESH_H_

#include "StandardIncludes.h"
#include "Shader.h"

class Mesh
{
public:
    ~Mesh();
    void Create(Shader* shader, glm::vec3 pos, glm::vec3 color);
    void Render(glm::mat4 VP);

    void SetPosition(glm::vec3 pos) { position = pos; }
    glm::vec3 GetPosition() const { return position; }
    void SetTouched(bool touched) { isTouched = touched; }
    void SetColor(glm::vec3 col) { baseColor = col; }
    void SetRotationZ(float angle) { rotationZ = angle; }

private:
    Shader* shader;
    GLuint vertexBuffer;
    std::vector<float> vertexData;
    glm::vec3 position;
    glm::vec3 baseColor;
    float rotationZ = 0.0f;
    bool isTouched;
};

#endif //!_MESH_H_