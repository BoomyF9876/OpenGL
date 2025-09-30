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
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);//Ensure we can capture the escape key
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);//Dark blue background

	camera = new Camera(WindowController::GetInstance().GetResolution());
	shader = new Shader();
	shader->LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");

	InitPlayer();
	InitNPCs();

	std::srand((unsigned)time(0));
}
void GameController::InitPlayer()
{
	player = new Mesh();
	player->Create(shader, glm::vec3(0, 0, 0), glm::vec3(1, 0, 0)); // 红色
}

void GameController::InitNPCs()
{
	for (int i = 0; i < 10; i++)
	{
		float x = (std::rand() % 2 == 0 ? 1 : -1) * (2 + (std::rand() % 9)); // [2,10] 或 [-10,-2]
		float y = (std::rand() % 2 == 0 ? 1 : -1) * (2 + (std::rand() % 9));

		Mesh* npc = new Mesh();
		npc->Create(shader, glm::vec3(x, y, 0), glm::vec3(0, 1, 0)); // 绿色
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

		if (dist < 1.0f)
		{
			npc->SetColor(glm::vec3(0, 0, 1)); 
		}
		else
		{
			npc->SetColor(glm::vec3(0, 1, 0)); 
		}

		if (dist > 0.0001f)
			dir = glm::normalize(dir);


		float speed = 2.0f * deltaTime;
		if (dist < 10.0f)
			npcPos -= dir * speed;
		else if (dist > 11.0f)
			npcPos += dir * speed;

		npc->SetPosition(npcPos);

		float angle = atan2(playerPos.y - npcPos.y, playerPos.x - npcPos.x);
		npc->SetRotationZ(angle);
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

		// 渲染
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