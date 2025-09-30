#pragma once
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include"StandardIncludes.h"

class Texture
{
public:
	~Texture();

	GLuint GetTexture() { return texture; }
	void LoadTexture(std::string _filename);

private:
	int width = -1;
	int height = -1;
	int channels = -1;
	GLuint texture;

};


#endif 




