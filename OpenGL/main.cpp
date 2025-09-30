// OpenGL.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<vector>
#include<cassert>
#include<string>
#include<fstream>

//Widows specific includes and defines
#ifdef _WIN32
#include <Windows.h>
#endif

//Open Gl/Helpers headers
#include <gl/glew.h> //Include GLEW
#include <GLFW/glfw3.h>  //Include GLFW
#include <glm/glm.hpp>   //Include GLM
#include<glm/gtc/matrix_transform.hpp>

#include"ToolWindow.h"
#include"StandardIncludes.h"
#include"GameController.h"


int main(void)
{
	GameController* gameController = new GameController();
	gameController->Initialize();
	gameController->RunGame();
}

