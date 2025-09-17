#pragma once

#ifndef _STANDARDINCLUDES_H_
#define _STANDARDINCLUDES_H_

#include <vector>
#include <cassert>
#include <string>
#include <fstream>

//Window specific includes and defines
#ifdef _WIN32
#include <Windows.h>
#define M_ASSERT(_cond, _msg)\
	if(!(_cond)){OutputDebugStringA(_msg); std::abort(); glfwTerminate();} 
#endif

//Open GL/Helper headers
#include <GL/glew.h> //Include GLEW
#include <GLFW/glfw3.h> //Include GLFW
#include <glm/glm.hpp> //Include GLM
#include<glm/gtc/matrix_transform.hpp>

#endif //!_STANDARDINCLUDES_H_