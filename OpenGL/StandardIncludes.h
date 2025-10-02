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
#define GLM_ENABLE_EXPERIMENTAL

//Open GL/Helper headers
#include <GL/glew.h> //Include GLEW
#include <GLFW/glfw3.h> //Include GLFW
#include <glm/glm.hpp> //Include GLM
#include<glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Resolution.h"

#endif //!_STANDARDINCLUDES_H_