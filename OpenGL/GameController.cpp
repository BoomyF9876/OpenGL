#include "GameController.h"
#include "WindowController.h"
#include "ToolWindow.h"

void GameController::Initialize()
{
	GLFWwindow* window = WindowController::GetInstance().GetWindow();

	M_ASSERT(glewInit() == GLEW_OK, "Unable to initialize glew");
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);//Ensure we can capture the escape key
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);//Dark blue background
}

void GameController::RunGame()
{
	shader = new Shader();
	shader->LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");
	mesh = new Mesh();
	mesh->Create(shader);

	OpenGL::ToolWindow^ toolWindow = gcnew OpenGL::ToolWindow();
	toolWindow->Show();

	GLFWwindow* window = WindowController::GetInstance().GetWindow();
	do
	{
		System::Windows::Forms::Application::DoEvents();
		GLint loc = 0;
		loc = glGetUniformLocation(shader->GetProgramID(), "RenderRedChannel");
		glUniform1i(loc, (int)OpenGL::ToolWindow::RenderRedChannel);
		loc = glGetUniformLocation(shader->GetProgramID(), "RenderGreenChannel");
		glUniform1i(loc, (int)OpenGL::ToolWindow::RenderGreenChannel);
		loc = glGetUniformLocation(shader->GetProgramID(), "RenderBlueChannel");
		glUniform1i(loc, (int)OpenGL::ToolWindow::RenderBlueChannel);

		GLint intensityLoc = glGetUniformLocation(shader->GetProgramID(), "Intensity");
		glUniform1f(intensityLoc, OpenGL::ToolWindow::Intensity);
		
		glClear(GL_COLOR_BUFFER_BIT);
		mesh->Render();
		
		glfwSwapBuffers(window);// Swap front and back buffers
		glfwPollEvents();

	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && //check if the ESC key was pressed
		glfwWindowShouldClose(window) == 0);//check if the window was closed

	delete mesh;
	delete shader;
}