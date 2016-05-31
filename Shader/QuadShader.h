#pragma once

/** @file QuadShader.h
*@brief Quad shader class file.
*/

#include "Shader.h"

/** Quad buffer shader.
*/
class QuadShader : public Shader {
public:
	/** Constructor.
	  * @param z_near distance of near plane
	  * @param z_far distance of near plane
	  * @param angle drill angle of cutaway surface cones
	  * @param texDim dimension of used texture in frame buffer object
	  */
	QuadShader(float z_near, float z_far, float angle, glm::vec2 texDim);
	~QuadShader();
};