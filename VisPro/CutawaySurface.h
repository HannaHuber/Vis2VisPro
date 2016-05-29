#pragma once

#include "ZBufferShader.h"
#include "Quad.h"
#include "QuadShader.h"
#include <memory>

class CutawaySurface {
public: 
	CutawaySurface();
	~CutawaySurface();

	void init(int w, int h, float z_near, float z_far, float angle, float cut);

	void update(int w, int h, float z_near, float z_far, float angle, float c);
	void prepareZBufferPass();
	void endZBufferPass();
	void quadPass(int step, glm::mat4& vp);
	void prepareRenderPass(int unit);
	glm::vec2 getDimension();
	GLuint getTextureHandle(int tex);
	GLuint getFBOHandle(int fbo);
	
	ZBufferShader* z_buffer_shader;
	Quad* quad;
	QuadShader* quad_shader;

	float cut;
private:
	GLuint tex1, tex2, look_up_tex, target_tex, fbo1, fbo2, target_fbo;
	int width, height, last_target;
};