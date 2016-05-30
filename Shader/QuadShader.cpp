#include "QuadShader.h"
#include "gtc/type_ptr.hpp"

using namespace glm;


QuadShader::QuadShader(float z_near, float z_far, float angle, vec2 texDim)
: Shader("./Shader/QuadShader.vert", "./Shader/QuadShader.frag")
{
	useShader();

	// Set projection matrix z-scaling factor
	float pmsz = (z_near + z_far) / (z_near - z_far);
	auto pmsz_location = glGetUniformLocation(programHandle, "PMsz");
	glUniform1f(pmsz_location, pmsz);
	
	// Set tangent of drill angle
	float tanPhiInv = glm::atan(glm::radians(angle));//1.0f / glm::tan(glm::radians(angle));
	auto tanphi_location = glGetUniformLocation(programHandle, "tanPhiInv");
	glUniform1f(tanphi_location, tanPhiInv);

	// Set texture dimensions
	setCutawayDimension(texDim);

	glUseProgram(0);
}

QuadShader::~QuadShader() {

}