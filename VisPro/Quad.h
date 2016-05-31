#pragma once

/** @file Quad.h
*@brief Quad class file.
*/

#include "glew.h"
#include "glfw3.h"
#include <list>
#include <vector>

/** Defines a quad out of four vertices. 
 */
class Quad {
public:
	Quad();
	~Quad();
	void useShader();
	void bindVAO();
private:
	GLuint vao, vbo;
	static GLfloat vertices[24];
	
};

