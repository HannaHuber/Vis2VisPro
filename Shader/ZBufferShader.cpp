#include "ZBufferShader.h"

ZBufferShader::ZBufferShader(glm::vec2 dim)
: Shader("./Shader/ZBufferShader.vert", "./Shader/ZBufferShader.frag")
{
	setCutawayDimension(dim);
}

ZBufferShader::~ZBufferShader() {

}