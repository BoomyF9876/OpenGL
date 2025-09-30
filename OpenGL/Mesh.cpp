#include "Mesh.h"

Mesh::~Mesh()
{
	glDeleteBuffers(1, &vertexBuffer);
}

void Mesh::Create(Shader* _shader, glm::vec3 pos, glm::vec3 color)
{
    shader = _shader;
    position = pos;
    baseColor = color;
    rotationZ = 0.0f;


    vertexData = {
         0.0f,  0.5f, 0.0f,  1.0f,0.0f,0.0f,1.0f,
        -0.5f, -0.5f, 0.0f,   0.0f,1.0f,0.0f,1.0f,
         0.5f, -0.5f, 0.0f,   0.0f,0.0f,1.0f,1.0f, 
    };

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), vertexData.data(), GL_STATIC_DRAW);
}

void Mesh::Render(glm::mat4 VP)
{
    glUseProgram(shader->GetProgramID());

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::rotate(model, rotationZ, glm::vec3(0, 0, 1));

    glm::mat4 WVP = VP * model;
    glUniformMatrix4fv(shader->GetAttrWVP(), 1, GL_FALSE, &WVP[0][0]);

    vertexData[3] = baseColor.r;
    vertexData[4] = baseColor.g;
    vertexData[5] = baseColor.b;
    vertexData[10] = baseColor.r;
    vertexData[11] = baseColor.g;
    vertexData[12] = baseColor.b;
    vertexData[17] = baseColor.r;
    vertexData[18] = baseColor.g;
    vertexData[19] = baseColor.b;

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertexData.size() * sizeof(float), vertexData.data());

    glEnableVertexAttribArray(shader->GetAttrVertices());
    glVertexAttribPointer(
        shader->GetAttrVertices(),
        3,
        GL_FLOAT,
        GL_FALSE,
        7 * sizeof(float),
        (void*)0
    );

    glEnableVertexAttribArray(shader->GetAttrColor());
    glVertexAttribPointer(
        shader->GetAttrColor(),
        4,
        GL_FLOAT,
        GL_FALSE,
        7 * sizeof(float),
        (void*)(3 * sizeof(float))
    );

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableVertexAttribArray(shader->GetAttrVertices());
    glDisableVertexAttribArray(shader->GetAttrColor());
}