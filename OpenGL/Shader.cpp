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
	attrVertices = glGetAttribLocation(programID, "inPosition");
	attrColor = glGetAttribLocation(programID, "inColor");
	attrWVP = glGetUniformLocation(programID, "WVP");
}

void Shader::EvaluateShader(int infoLength, GLuint id)
{
	if (infoLength > 0)
	{
		std::vector<char> errorMessage(infoLength + 1);
		glGetShaderInfoLog(id, infoLength, NULL, &errorMessage[0]);
		printf("Shader Error: %s\n", &errorMessage[0]);
	}
}

void Shader::CreateShaderProgram(const char* vertexFilePath, const char* fragmentFilePath)
{
	programID = glCreateProgram();
	GLuint vertexShaderID = LoadShaderFile(vertexFilePath, GL_VERTEX_SHADER);
	GLuint fragmentShaderID = LoadShaderFile(fragmentFilePath, GL_FRAGMENT_SHADER);

	glLinkProgram(programID);

	glGetProgramiv(programID, GL_LINK_STATUS, &result);
	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
	EvaluateShader(infoLogLength, programID);

	glDetachShader(programID, vertexShaderID);
	glDetachShader(programID, fragmentShaderID);
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
}

void Shader::LoadShaders(const char* vertexFilePath, const char* fragmentFilePath)
{
	CreateShaderProgram(vertexFilePath, fragmentFilePath);
	LoadAttributes();
}

GLuint Shader::LoadShaderFile(const char* filePath, GLenum type)
{
	GLuint shaderID = glCreateShader(type);

	std::string shaderCode;
	std::ifstream shaderStream(filePath, std::ios::in);

	if (!shaderStream.is_open())
	{
		printf("Can not open %s\n", filePath);
		return 0;
	}

	std::string line = "";
	while (getline(shaderStream, line))
	{
		shaderCode += "\n" + line;
	}
	shaderStream.close();

	const char* shaderSource = shaderCode.c_str();
	glShaderSource(shaderID, 1, &shaderSource, NULL);
	glCompileShader(shaderID);

	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
	EvaluateShader(infoLogLength, shaderID);

	glAttachShader(programID, shaderID);
	return shaderID;
}
	