#pragma once

/** @file ZBufferShader.h
*@brief Z buffer shader class file.
*/

#include "Shader.h"

/** Z buffer shader.
*/
class ZBufferShader : public Shader {
public:
	/** Constructor.
	  * @param dim screen dimension of z buffer
	  */
	ZBufferShader(glm::vec2 dim);

	~ZBufferShader();
};