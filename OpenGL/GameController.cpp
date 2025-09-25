#include "GameController.h"
#include "WindowController.h"
#include "ToolWindow.h"

GameController::GameController()
{
	cameras[0] = new Camera(resolutions[0]);
	cameras[1] = new Camera(resolutions[1]);
	cameras[2] = new Camera(resolutions[2]);
	cameras[3] = new Camera(resolutions[3]);

	//LookAt(const glm::vec3& _position, const glm::vec3& _lookAt, const glm::vec3& _up);
	cameras[0]->LookAt({200,200,200},{0,0,0}, {0,1,0});
	cameras[1]->LookAt({-200,-200,-200},{0,0,0}, {0,1,0});
	cameras[2]->LookAt({100,300,100}, {0,0,0}, {0,1,0});
	cameras[3]->LookAt({400,0,0},{0,0,0}, {0,1,0});

}

GameController::~GameController() {
    for (int i = 0; i < 4; ++i) {
        delete cameras[i];
    }
	delete mesh;
	delete shader;
}

void GameController::Initialize()
{
	GLFWwindow* window = WindowController::GetInstance().GetWindow();

	M_ASSERT(glewInit() == GLEW_OK, "Unable to initialize glew");
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);//Ensure we can capture the escape key
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);//Dark blue background
	glEnable(GL_CULL_FACE);	

}

void GameController::UpdateAllProjections(float fov, float nearPlane, float farPlane)
{
	for (int i = 0; i < 4; ++i)
	{
		if (cameras[i])
		{
			const Resolution& res = resolutions[currentResolutionIndex];
			glm::mat4 proj = glm::perspective(glm::radians(fov),
				(float)res.width / (float)res.height,
				nearPlane,
				farPlane);
			cameras[i]->SetProjection(proj);
		}
	}
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

	bool cWasPressed = false;
	bool vWasPressed = false;
	double startTime = glfwGetTime();
	do
	{
		System::Windows::Forms::Application::DoEvents();


		if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
			if (!cWasPressed) {
				currentCameraIndex = (currentCameraIndex + 1) % 4; // remainder
				cWasPressed = true;
			}
		}
		else {
			cWasPressed = false;
		}

		if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
		{
			if (!vWasPressed)
			{
				currentResolutionIndex = (currentResolutionIndex + 1) % 4;
				Resolution& newRes = resolutions[currentResolutionIndex];
				WindowController::GetInstance().ResizeWindow(newRes);
				UpdateAllProjections();

				vWasPressed = true;
			}
		}
		else
		{
			vWasPressed = false;
		}


		GLint loc = 0;
		loc = glGetUniformLocation(shader->GetProgramID(), "RenderRedChannel");
		glUniform1i(loc, (int)OpenGL::ToolWindow::RenderRedChannel);
		loc = glGetUniformLocation(shader->GetProgramID(), "RenderGreenChannel");
		glUniform1i(loc, (int)OpenGL::ToolWindow::RenderGreenChannel);
		loc = glGetUniformLocation(shader->GetProgramID(), "RenderBlueChannel");
		glUniform1i(loc, (int)OpenGL::ToolWindow::RenderBlueChannel);

		GLint intensityLoc = glGetUniformLocation(shader->GetProgramID(), "Intensity");
		glUniform1f(intensityLoc, OpenGL::ToolWindow::Intensity);


		//WASD 
		
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) 
		{ 
			rotationX -= 1.0f;
		} 
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) 
		{ 
			rotationY -= 1.0f;
		} 
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) 
		{ 
			rotationX += 1.0f;
		} 
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			rotationY += 1.0f;
		}

		glm::mat4 world = glm::mat4(1.0f);
		world = glm::rotate(world, glm::radians(rotationX), glm::vec3(1, 0, 0));
		world = glm::rotate(world, glm::radians(rotationY), glm::vec3(0, 1, 0));


		
		double currentTime = glfwGetTime() - startTime; 

		const float MIN_SCALE = 0.01f;    
		const float MAX_SCALE = 2.0f;     
		const float PERIOD = 2.0f;        

		float phase = fmod((float)currentTime, PERIOD) / (float)PERIOD;

		const float PI = glm::pi<float>();
		float eased = (sin(phase * 2.0f * PI) + 1.0f) / 2.0f;

		float finalScale = MIN_SCALE + eased * (MAX_SCALE - MIN_SCALE);

		world = glm::scale(world, glm::vec3(finalScale));

		
		glClear(GL_COLOR_BUFFER_BIT);
		mesh->Render(cameras[currentCameraIndex]->GetProjection() * cameras[currentCameraIndex]->GetView()*world);

		
		glfwSwapBuffers(window);// Swap front and back buffers
		glfwPollEvents();

	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && //check if the ESC key was pressed
		glfwWindowShouldClose(window) == 0);//check if the window was closed

	delete mesh;
	delete shader;
}