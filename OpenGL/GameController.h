#pragma once

#ifndef _GAMECONTROLLER_H_
#define _GAMECONTROLLER_H_

#include "StandardIncludes.h"
#include "Shader.h"
#include "Mesh.h"
#include "Camera.h"

class GameController
{
public:
    GameController();
    ~GameController();

    void Initialize();
    void RunGame();

    void UpdateAllProjections(float fov = 45.0f, float nearPlane = 0.1f, float farPlane = 1000.0f);

private:
    Shader* shader = nullptr;
    Mesh* mesh = nullptr;

    Camera* cameras[4]; 
    Resolution resolutions[4] ={
    Resolution(1024, 768),
    Resolution(900, 1080),
    Resolution(700, 900),
    Resolution(800,700) };

    int currentCameraIndex = 0;
    int currentResolutionIndex = 0;
};
#endif //!_GAMECONTROLLER_H_
