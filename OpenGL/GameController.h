#pragma once
#include "Camera.h"
#include "Shader.h"
#include "Mesh.h"
#include <GLFW/glfw3.h>

class GameController
{
private:
    Camera* camera = nullptr;

    // Shaders
    Shader* shaderColor = nullptr;
    Shader* shaderDiffuse = nullptr;

    Mesh* sun = nullptr;
    Mesh* earth = nullptr;
    Mesh* moon = nullptr;

    double lastTime = 0.0;

public:
    void Initialize();
    void RunGame();
    void LoadSolarSystem();
    void LoadSettingsFromJSON();
};
