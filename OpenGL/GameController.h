#pragma once

#ifndef _GAMECONTROLLER_H_
#define _GAMECONTROLLER_H_

#include "StandardIncludes.h"
#include "Shader.h"
#include "Mesh.h"
#include "Camera.h"
#include <vector>

class GameController
{
public:
    void Initialize();
    void RunGame();

private:
    Shader* shader;
    Camera* camera;
    Mesh* player;
    std::vector<Mesh*> npcs; 

    void InitPlayer();
    void InitNPCs();
    void UpdateNPCs(float deltaTime);
};
#endif //!_GAMECONTROLLER_H_
