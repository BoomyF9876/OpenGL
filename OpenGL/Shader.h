#pragma once

#ifndef _SHADER_H_
#define _SHADER_H_

#include "StandardIncludes.h"


class Shader
{
public:
	~Shader();

	GLuint GetProgramID(){return programID;}
	GLuint GetAttrVertices(){return attrVertices;}
	GLuint GetAttrWVP() { return attrWVP; }
	GLuint GetAttrColor() { return attrColor; }
	GLuint GetAttrTexCoords() { return attrTexCoords; }
	GLuint GetTexSampler1() { return attrTexSampler1; }
	GLuint GetTexSampler2() { return attrTexSampler2; }
	GLuint GetAttrTangents() { return attrTangents; }
	GLuint GetAttrBitangents() { return attrBitangents; }
	GLuint GetAttrTexScroll() { return attrTexScroll; }
	GLuint GetAttrNormals() { return attrNormals; }
	GLuint GetAttrInstanceMatrix() { return attrInstanceMatrix; }

	void SetVec3(const char* _name, glm::vec3 _value);
	void SetMat4(const char* _name, glm::mat4 _value);
	void SetInt(const char* _name, int _value);
	void SetFloat(const char* _name, float _value);
	void SetTextureSampler(const char* _name, GLuint _texUint, int _texUintId, int _value);
	void LoadShaders(const char* _vertexFilePath, const char* _fragmentFilePath);

private:
	void CreateShaderProgram(const char* _vertexFilePath, const char* _fragmentFilePath);
	GLuint LoadShaderFile(const char* _filePath, GLenum _type);
	void LoadAttributes();
	void EvaluateShader(int _infoLength, GLuint _id);

	GLuint programID = 0;
	GLuint attrVertices = 0;
	GLuint attrWVP = 0;
	GLuint attrColor = 0;
	GLuint attrTexCoords = 0;
	GLuint attrTexSampler1 = 0;
	GLuint attrTexSampler2 = 0;
	GLuint attrTexScroll = 0;
	GLuint attrNormals = 0;
	GLuint attrInstanceMatrix = 0;
	GLuint attrTangents = 0;
	GLuint attrBitangents = 0;

	GLint result = GL_FALSE;
	int infoLogLength = 0;
};

#endif _SHADER_H_

