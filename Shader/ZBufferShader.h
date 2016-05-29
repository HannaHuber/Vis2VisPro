#pragma once

#include "Shader.h"

class ZBufferShader : public Shader {
public:
	ZBufferShader(glm::vec2 dim);
	~ZBufferShader();
};