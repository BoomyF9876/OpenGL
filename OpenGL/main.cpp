// OpenGL.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include"GameController.h"

//<Summary>
//Initializes OpenGL settings and creates a window which is its OpenGL context
//</Summary>
//GLFWwindow* Initialize()
//{
//	GLFWwindow* _window = nullptr;
//
//	assert(glfwInit(), "Failed to initialize GLFW");// Initialize GLFW
//	glfwWindowHint(GLFW_SAMPLES, 4);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
//	_window = glfwCreateWindow(1024, 768, "A sample scene", NULL, NULL); // Create a windowed mode window and its OpenGL context 
//	assert(_window != nullptr, "Failed to open GLFW window. ");
//	glfwMakeContextCurrent(_window); // Make the window's context current
//
//	assert(glewInit() == GLEW_OK, throw std::exception); // Initialize GLEW
//	glfwSetInputMode(_window, GLFW_STICKY_KEYS, GL_TRUE);
//	glClearColor(0.0f, 0.0f, 0.4f, 0.0f); // Dark blue background
//
//	return _window;
//}
//
//void EvaluateShader(int _infoLength, GLuint _id)
//{
//	if (_infoLength > 0)
//	{
//		std::vector<char> errorMessage(_infoLength + 1);
//		glGetShaderInfoLog(_id, _infoLength, NULL, &errorMessage[0]);
//		assert(NULL, ("%s\n", &errorMessage[0]));
//	}
//}

//GLuint LoadShaderFile(const char* _filePath, GLenum _type, GLuint programID)
//{
//	GLuint shaderID = glCreateShader(_type); // Create the shader
//
//	//Read the Shader code from the file
//	std::string shaderCode;
//	std::ifstream shaderStream(_filePath, std::ios::in);
//	bool isOpen = shaderStream.is_open();
//	assert(shaderStream.is_open(), ("Impossible to open %s. Are you in the right directory? "
//		"Don't forget to read the FAQ !\n", _filePath));
//	std::string Line = "";
//	while (getline(shaderStream, Line))
//	{
//		shaderCode += "\n" + Line;
//	}
//	shaderStream.close();
//
//
//	// Compile Shader
//	char const* sourcePointer = shaderCode.c_str();
//	glShaderSource(shaderID, 1, &sourcePointer, NULL);
//	glCompileShader(shaderID);
//
//	// Check Shader
//	GLint result = GL_FALSE;
//	int infoLogLength = 0;
//	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
//	glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
//	EvaluateShader(infoLogLength, shaderID);
//
//	// Attach shader to program
//	glAttachShader(programID, shaderID);
//
//	return shaderID;
//}
//
//GLuint CreateShaderProgram(const char* _vertexFilePath, const char* _fragmentFilePath)
//{
//	GLuint programID = glCreateProgram(); // Create the shader program
//
//	GLuint vertexShaderID = LoadShaderFile(_vertexFilePath, GL_VERTEX_SHADER, programID); //Load vertex shader
//	GLuint fragmentShaderID = LoadShaderFile(_fragmentFilePath, GL_FRAGMENT_SHADER, programID); //Load fragment shader
//	glLinkProgram(programID); // LInk the program
//
//	//Check the program
//	GLint result = GL_FALSE;
//	int infoLogLenth = 0;
//	glGetProgramiv(programID, GL_LINK_STATUS, &result);
//	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLenth);
//	EvaluateShader(infoLogLenth, programID);
//
//	// Free resources
//	glDetachShader(programID, vertexShaderID);
//	glDetachShader(programID, fragmentShaderID);
//	glDeleteShader(vertexShaderID);
//	glDeleteShader(fragmentShaderID);
//
//	return programID;
//
//
//}


int main(void)
{
	GameController::GetInstance().Initialize();
	GameController::GetInstance().RunGame();
	//OpenGL::ToolWindow^ toolWindow = gcnew OpenGL::ToolWindow();
	//toolWindow->Show();

	//GLFWwindow* window = Initialize();

	//GLuint programID = CreateShaderProgram("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");
	//GLuint attrVertices = glGetAttribLocation(programID, "vertices");

	//GLuint vertexBuffer = 0;
	//std::vector<GLfloat>vertexData;
	//vertexData = { -1.0f,-1.0f,0.0f,
	//	1.0f,-1.0f,0.0f,
	//	0.0f,1.0f,0.0f };
	//glGenBuffers(1, &vertexBuffer);
	//glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	//glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), vertexData.data(), GL_STATIC_DRAW);


	//do
	//{
	//	System::Windows::Forms::Application::DoEvents();

	//	GLint loc = 0;
	//	loc = glGetUniformLocation(programID, "RenderRedChannel");
	//	glUniform1i(loc, (int)OpenGL::ToolWindow::RenderRedChannel);
	//	loc = glGetUniformLocation(programID, "RenderGreenChannel");
	//	glUniform1i(loc, (int)OpenGL::ToolWindow::RenderGreenChannel);
	//	loc = glGetUniformLocation(programID, "RenderBlueChannel");
	//	glUniform1i(loc, (int)OpenGL::ToolWindow::RenderBlueChannel);
	//	// Render here
	//	glClear(GL_COLOR_BUFFER_BIT);

	//	glUseProgram(programID);

	//	glEnableVertexAttribArray(attrVertices);
	//	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	//	glVertexAttribPointer(
	//		attrVertices,
	//		3, 
	//		GL_FLOAT, 
	//		GL_FALSE, 
	//		0,
	//		(void*)0
	//	);

	//	// Draw the triangle !
	//	glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
	//	glDisableVertexAttribArray(attrVertices);

	//	// Swap front and back buffers
	//	glfwSwapBuffers(window);
	//	// Poll for and process events
	//	glfwPollEvents();

	//} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
	//	glfwWindowShouldClose(window) == 0);

	//glDeleteBuffers(1, &vertexBuffer);
	//glfwTerminate();

	//if (programID != 0)
	//{
	//	glDeleteProgram(programID);
	//}

	//return 0;
}

