#pragma once

/** @file Texture.h
*@brief Texture class file.
*/

#include "glew.h"
#include <string>

class Texture {
public:
	Texture(const std::string& path);
	~Texture();

	/** Bind texture to given texture unit. 
	  */
	void bind(int unit);

private:
	unsigned char* loadFile(const char* path);
	GLuint handle;
	unsigned char* data;
	int width, height;

};