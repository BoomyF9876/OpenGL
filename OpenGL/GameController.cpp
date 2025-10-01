#include "GameController.h"
#include "WindowController.h"
#include "ToolWindow.h"

void GameController::Initialize()
{
	GLFWwindow* window = WindowController::GetInstance().GetWindow();

	M_ASSERT(glewInit() == GLEW_OK, "Unable to initialize glew");
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);//Ensure we can capture the escape key
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);//Dark blue background
	glEnable(GL_CULL_FACE);

	camera = new Camera(WindowController::GetInstance().GetResolution());
	camera->LookAt({ 100,100,100 }, { 0,0,0 }, { 0,1,0 });
}

void GameController::RunGame()
{
	shader = new Shader();
	shader->LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");
	mesh = new Mesh();
	mesh->Create(shader);

	OpenGL::ToolWindow^ toolWindow = gcnew OpenGL::ToolWindow();
	//toolWindow->Show();

	GLFWwindow* window = WindowController::GetInstance().GetWindow();
	do
	{
		glClear(GL_COLOR_BUFFER_BIT);
		mesh->Render(camera->GetProjection()*camera->GetView());
		
		glfwSwapBuffers(window);// Swap front and back buffers
		glfwPollEvents();

	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && //check if the ESC key was pressed
		glfwWindowShouldClose(window) == 0);//check if the window was closed

	delete mesh;
	delete shader;
}