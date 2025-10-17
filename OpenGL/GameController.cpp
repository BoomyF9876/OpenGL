#include "GameController.h"
#include "WindowController.h"
#include "ToolWindow.h"
#include <fstream>


void GameController::Initialize()
{
    GLFWwindow* window = WindowController::GetInstance().GetWindow();
    M_ASSERT(glewInit() == GLEW_OK, "Unable to initialize glew");
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glEnable(GL_DEPTH_TEST);

    camera = new Camera(WindowController::GetInstance().GetResolution());

    LoadSettingsFromJSON();
}

void GameController::LoadSettingsFromJSON()
{
    json::JSON root = LoadJSON("settings.json");
    auto cam = root.at("Camera");

    glm::vec3 camPos = { (float)cam["Position"]["x"].ToFloat(),
                         (float)cam["Position"]["y"].ToFloat(),
                         (float)cam["Position"]["z"].ToFloat() };

    glm::vec3 camLookAt = { (float)cam["LookAt"]["x"].ToFloat(),
                            (float)cam["LookAt"]["y"].ToFloat(),
                            (float)cam["LookAt"]["z"].ToFloat() };

    camera->LookAt(camPos, camLookAt, { 0, 1, 0 });
}

void GameController::LoadSolarSystem()
{
    shaderColor = new Shader();
    shaderColor->LoadShaders("Color.vertexshader", "Color.fragmentshader");

    shaderDiffuse = new Shader();
    shaderDiffuse->LoadShaders("Diffuse.vertexshader", "Diffuse.fragmentshader");

    sun = new Mesh();
    sun->LoadFromJSON("sun.json", shaderColor);

    earth = new Mesh();
    earth->LoadFromJSON("earth.json", shaderDiffuse);
    earth->SetLightPosition(sun->GetPosition());
    earth->SetLightColor(sun->GetLightColor());

    moon = new Mesh();
    moon->LoadFromJSON("moon.json", shaderDiffuse);
    moon->SetLightPosition(sun->GetPosition());
    moon->SetLightColor(sun->GetLightColor());

    OpenGL::ToolWindow::LightR = sun->GetLightColor().r;
    OpenGL::ToolWindow::LightG = sun->GetLightColor().g;
    OpenGL::ToolWindow::LightB = sun->GetLightColor().b;

    OpenGL::ToolWindow::Position_X = earth->GetPosition().x;
    OpenGL::ToolWindow::Position_Y = earth->GetPosition().y;
    OpenGL::ToolWindow::Position_Z = earth->GetPosition().z;
}

void GameController::RunGame()
{
    LoadSolarSystem();

    OpenGL::ToolWindow^ toolWindow = gcnew OpenGL::ToolWindow();
    toolWindow->Show(); 

    GLFWwindow* window = WindowController::GetInstance().GetWindow();
    lastTime = glfwGetTime();

    do
    {
        double currentTime = glfwGetTime();
        float deltaTime = float(currentTime - lastTime);
        lastTime = currentTime;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::vec3 lightColor(
            OpenGL::ToolWindow::LightR,
            OpenGL::ToolWindow::LightG,
            OpenGL::ToolWindow::LightB
        );

        glm::vec3 earthPos(
            OpenGL::ToolWindow::Position_X,
            OpenGL::ToolWindow::Position_Y,
            OpenGL::ToolWindow::Position_Z
        );

        float rotationRate = OpenGL::ToolWindow::Rotation_Rate;

        sun->SetLightColor(lightColor);
        sun->SetRotationRate(rotationRate);

		earth->SetPosition(earthPos);
        earth->SetLightPosition(sun->GetPosition());
        earth->SetLightColor(lightColor);
        earth->SetRotationRate(rotationRate);

        moon->SetLightPosition(sun->GetPosition());
        moon->SetLightColor(lightColor);
        moon->SetRotationRate(rotationRate);

        sun->Update(deltaTime);
        earth->Update(deltaTime);
        moon->Update(deltaTime);

        glm::mat4 pv = camera->GetProjection() * camera->GetView();
        sun->Render(pv);

        earth->SetParent(sun->GetWorld());
        earth->Render(pv);

        moon->SetParent(earth->GetWorld());
        moon->Render(pv);

        glfwSwapBuffers(window);
        glfwPollEvents();

    } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
        glfwWindowShouldClose(window) == 0);

    delete sun;
    delete earth;
    delete moon;
    delete shaderColor;
    delete shaderDiffuse;
    delete camera;
}