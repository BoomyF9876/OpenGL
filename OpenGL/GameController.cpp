#include "GameController.h"
#include "WindowController.h"
#include "ToolWindow.h"
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <ctime>
#include <cmath>


void GameController::Initialize()
{
	GLFWwindow* window = WindowController::GetInstance().GetWindow();
	M_ASSERT(glewInit() == GLEW_OK, "Unable to initialize glew");
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	Resolution res = WindowController::GetInstance().GetResolution();
	camera = new Camera(res, 45.0f, 0.1f, 100.0f);

	shader = new Shader();
	shader->LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");
	InitPlayer();
	InitNPCs();
	std::srand((unsigned)time(0));
}
void GameController::InitPlayer()
{
	player = new Mesh();
	player->Create(shader, glm::vec3(0, 0, 0), glm::vec3(1, 0, 0));
}

void GameController::InitNPCs()
{
	for (int i = 0; i < 10; i++)
	{
		float x = (std::rand() % 2 == 0 ? 1 : -1) * (2 + (std::rand() % 9));
		float y = (std::rand() % 2 == 0 ? 1 : -1) * (2 + (std::rand() % 9));

		Mesh* npc = new Mesh();
		npc->Create(shader, glm::vec3(x, y, 0), glm::vec3(0, 1, 0));
		npcs.push_back(npc);
	}
}

void GameController::UpdateNPCs(float deltaTime)
{
	glm::vec3 playerPos = player->GetPosition();

	for (auto& npc : npcs)
	{
		glm::vec3 npcPos = npc->GetPosition();
		glm::vec3 dir = playerPos - npcPos;
		float dist = glm::length(dir);

		if (dist < 1.0f && !npc->GetIsTouched())
		{
			npc->SetTouched(true);
			npc->SetColor(glm::vec3(0, 0, 1));
		}

		if (npc->GetIsTouched())
		{
			npc->SetColor(glm::vec3(0, 0, 1));
		}

		if (dist > 0.0001f)
			dir = glm::normalize(dir);


		float speed = 1.0f * deltaTime;
		if (dist < 5.0f)
			npcPos -= dir * speed;
		else if (dist > 6.0f)
			npcPos += dir * speed;

		npc->SetPosition(npcPos);

		float angle = atan2(playerPos.y - npcPos.y, playerPos.x - npcPos.x);
		npc->SetRotationZ(angle + glm::radians(270.0f));
	}
}

void GameController::RunGame()
{
	GLFWwindow* window = WindowController::GetInstance().GetWindow();
	double lastTime = glfwGetTime();
	do
	{
		double currentTime = glfwGetTime();
		float deltaTime = float(currentTime - lastTime);
		lastTime = currentTime;

		glm::vec3 pos = player->GetPosition();
		float speed = 5.0f * deltaTime;
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) pos.y += speed;
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) pos.y -= speed;
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) pos.x -= speed;
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) pos.x += speed;
		player->SetPosition(pos);

		UpdateNPCs(deltaTime);

		glClear(GL_COLOR_BUFFER_BIT);
		glm::mat4 VP = camera->GetProjection() * camera->GetView();
		player->Render(VP);
		for (auto& npc : npcs) npc->Render(VP);

		glfwSwapBuffers(window);
		glfwPollEvents();

	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && //check if the ESC key was pressed
		glfwWindowShouldClose(window) == 0);//check if the window was closed

	delete player;
	for (auto& npc : npcs) delete npc;
	delete shader;
}