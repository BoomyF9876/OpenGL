#include "WindowController.h"

WindowController::~WindowController()
{
	if (window != nullptr)
	{
		glfwTerminate();
		window = nullptr;
	}
}

void WindowController::NewWindow()
{
	M_ASSERT(glfwInit(), "Filed to initialize GLFW>");


	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	window = glfwCreateWindow(1024, 789, "A sample scene", NULL, NULL);
	M_ASSERT(window != NULL, "Failed to open GLFW window.");
	glfwMakeContextCurrent(window);
}
