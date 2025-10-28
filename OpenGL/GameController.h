#pragma once
#include "Camera.h"
#include "Shader.h"
#include "Mesh.h"
#include <GLFW/glfw3.h>
#include "StandardIncludes.h"

class GameController
{
private:
    Camera* camera = nullptr;

    // Shaders
    Shader* shaderColor = nullptr;
    Shader* shaderDiffuse = nullptr;

	Mesh* meshLight = nullptr;
    std::list<Mesh*> meshes;

    double lastTime = 0.0;

public:
    void Initialize();
    void RunGame();
    
    float GetDeltaTime() { return float(glfwGetTime() - lastTime); }
};
