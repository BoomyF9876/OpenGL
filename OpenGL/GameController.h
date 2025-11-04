#pragma once
#include "Camera.h"
#include "Shader.h"
#include "Mesh.h"
#include <GLFW/glfw3.h>
#include "StandardIncludes.h"

class GameController
{
public:
    static GameController& GetInstance()
    {
        static GameController instance;
        return instance;
	}

    void Initialize();
    void RunGame();

    Shader* GetShader(const char* shaderName)
    {
		auto itr = shaders.find(shaderName);
        assert(itr != shaders.end());
		return itr->second;
    }

private:
    void Load();

private:
    std::map<std::string, Shader*> shaders;

    std::list<Mesh*> meshes;
	std::list<Mesh*> lights;

	Camera* camera = nullptr;

private:
	inline explicit GameController() = default;
	inline ~GameController() = default;
	inline explicit GameController(const GameController&) = delete;
	inline GameController& operator=(const GameController&) = delete;
};
