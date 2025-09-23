#include "Shader.h"

Shader::~Shader()
{
	if (programID != 0)
	{
		glDeleteProgram(programID);
	}
}

void Shader::LoadAttributes()
{
	//Get a handle for our vertex attribute
	attrVertices = glGetAttribLocation(programID, "vertices");
	attrColor = glGetAttribLocation(programID, "colors");
	attrWVP = glGetUniformLocation(programID, "WVP");//Get a handle for WVP
}

void Shader::EvaluateShader(int _infoLength, GLuint _id)
{
	if (_infoLength > 0)
	{
		std::vector<char> errorMessage(_infoLength + 1);
		glGetShaderInfoLog(_id, _infoLength, NULL, &errorMessage[0]);
		assert(NULL, ("%s\n", &errorMessage[0]));
	}
}

void Shader::CreateShaderProgram(const char* _vertexFilePath, const char* _fragmentFilePath)
{
	programID = glCreateProgram(); //Create the shader program

	GLuint vertexShaderID = LoadShaderFile(_vertexFilePath, GL_VERTEX_SHADER); //Load vertex shader
	GLuint fragmentShaderID = LoadShaderFile(_fragmentFilePath, GL_FRAGMENT_SHADER); //Load fragment shader
	glLinkProgram(programID); //LInk the program

	//Check the program
	glGetProgramiv(programID, GL_LINK_STATUS, &result);
	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
	EvaluateShader(infoLogLength, programID);

	// Free resources
	glDetachShader(programID, vertexShaderID);
	glDetachShader(programID, fragmentShaderID);
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
}

void Shader::LoadShaders(const char* _vertexFilePath, const char* _fragmentFilePath)
{
	CreateShaderProgram(_vertexFilePath, _fragmentFilePath);
	LoadAttributes();
}

GLuint Shader::LoadShaderFile(const char* _filePath, GLenum _type)
{
	GLuint shaderID = glCreateShader(_type); //Create the shader

	//Read the Shader code from the file
	std::string shaderCode;
	std::ifstream shaderStream(_filePath, std::ios::in);
	bool isOpen = shaderStream.is_open();
	assert(shaderStream.is_open(), ("Impossible to open %s. Are you in the right directory? "
		"Don't forget to read the FAQ !\n", _filePath));
	std::string Line = "";
	while (getline(shaderStream, Line))
	{
		shaderCode += "\n" + Line;
	}
	shaderStream.close();

	//Compile Shader
	const char* shaderSource = shaderCode.c_str();
	glShaderSource(shaderID, 1, &shaderSource, NULL);
	glCompileShader(shaderID);

	//Check shader
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
	EvaluateShader(infoLogLength, shaderID);

	//Attach shader to program
	glAttachShader(programID, shaderID);

	return shaderID;
}

	