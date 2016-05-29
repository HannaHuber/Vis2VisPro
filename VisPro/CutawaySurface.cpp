#include "CutawaySurface.h"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

using namespace glm;
using namespace std;

// Constructor usable without OpenGL context
CutawaySurface::CutawaySurface()
: last_target(1)
{
	
}
CutawaySurface::~CutawaySurface() {
	if (tex1) {
		glDeleteTextures(1, &tex1);
	}
	if (tex2) {
		glDeleteTextures(1, &tex2);
	}
	if (fbo1) {
		glDeleteBuffers(1, &fbo1);
	}
	if (fbo2) {
		glDeleteBuffers(1, &fbo2);
	}
	if (z_buffer_shader) {
		delete z_buffer_shader; 
		z_buffer_shader = nullptr;
	}
	if (quad) {
		delete quad;
		quad = nullptr;
	}
	if (quad_shader) {
		delete quad_shader;
		quad_shader = nullptr;
	}
}

// Initialize with OpenGL context
void CutawaySurface::init(int w, int h, float z_near, float z_far, float angle, float c) {
	
	cut = c;

	width = w;
	height = h;

	// Init depth map
	glGenTextures(1, &tex1);
	glBindTexture(GL_TEXTURE_2D, tex1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LESS);
	glBindTexture(GL_TEXTURE_2D, 0);

	
	// Init framebuffer and attach depth map
	glGenFramebuffers(1, &fbo1);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo1);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, tex1, 0);
	GLenum DrawBuffers1[1] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, DrawBuffers1);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// Init second texture and framebuffer for jump flooding
	glGenTextures(1, &tex2);
	glBindTexture(GL_TEXTURE_2D, tex2);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);
	glGenFramebuffers(1, &fbo2);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo2);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, tex2, 0);
	GLenum DrawBuffers2[1] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, DrawBuffers2);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
		
	// Init z buffer shader
	z_buffer_shader = new ZBufferShader(vec2((float)width, (float)height));

	// Init quad + quad shader
	quad = new Quad();
	quad_shader = new QuadShader(z_near, z_far, angle, vec2((float) width, (float) height));
}

void CutawaySurface::update(int w, int h, float z_near, float z_far, float angle, float c)
{
	cut = c;

	width = w;
	height = h;

	z_buffer_shader = new ZBufferShader(vec2((float)width, (float)height));
	quad_shader = new QuadShader(z_near, z_far, angle, vec2((float)width, (float)height));
}

void CutawaySurface::prepareZBufferPass() {
	glDepthFunc(GL_GREATER);
	/*glCullFace(GL_FRONT);
	glEnable(GL_CULL_FACE);*/
	glDisable(GL_CULL_FACE);
	glViewport(0, 0, width, height);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo1);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
}
void CutawaySurface::endZBufferPass() {
	//glBindFramebuffer(GL_FRAMEBUFFER, 0);
	/*glDepthFunc(GL_LESS);
	glClearDepth(1.0);*/
	//glCullFace(GL_BACK);
}

void CutawaySurface::quadPass(int step, mat4& vp) {
	glViewport(0, 0, width, height);
	/*glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_ALWAYS);*/
	quad_shader->useShader();

	// Set step length
	auto step_location = glGetUniformLocation(quad_shader->programHandle, "step");
	glUniform1i(step_location, step);

	// Set view projection matrix
	auto view_proj_location = glGetUniformLocation(quad_shader->programHandle, "view_proj");
	glUniformMatrix4fv(view_proj_location, 1, GL_FALSE, glm::value_ptr(vp));
	/*mat4 proj = glm::ortho(0, width - 1, 0, height - 1);
	glUniformMatrix4fv(view_proj_location, 1, GL_FALSE, glm::value_ptr(proj));*/

	// Set model matrix
	auto model_location = glGetUniformLocation(quad_shader->programHandle, "model");
	glUniformMatrix4fv(model_location, 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0)));

	if (last_target == 2) {
		glBindFramebuffer(GL_FRAMEBUFFER, fbo1);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glActiveTexture(GL_TEXTURE0 + 0);
		glBindTexture(GL_TEXTURE_2D, tex2);
		last_target = 1;
	}
	else {
		glBindFramebuffer(GL_FRAMEBUFFER, fbo2);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glActiveTexture(GL_TEXTURE0 + 0);
		glBindTexture(GL_TEXTURE_2D, tex1);
		last_target = 2;
	}
	auto ztex_location = glGetUniformLocation(quad_shader->programHandle, "lookUpTexture");
	glUniform1i(ztex_location, 0);

	// Draw
	quad->bindVAO();
	glDisable(GL_DEPTH_TEST);
	
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);

	glUseProgram(0);

}


void CutawaySurface::prepareRenderPass(int unit) {
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);

	glActiveTexture(GL_TEXTURE0 + unit);
	if (last_target == 2) {
		glBindTexture(GL_TEXTURE_2D, tex2);
		//glBindTexture(GL_TEXTURE_2D, tex1);
	}
	else {
		glBindTexture(GL_TEXTURE_2D, tex1);
	}
}

GLuint CutawaySurface::getTextureHandle(int tex)
{
	switch (tex)
	{
	case 1:
		return tex1;
	case 2:
		return tex2;
	default:
		return tex1;
	}
}

GLuint CutawaySurface::getFBOHandle(int fbo)
{
	switch (fbo)
	{
	case 1:
		return fbo1;
	case 2:
		return fbo2;
	default:
		return fbo1;
	}
}

vec2 CutawaySurface::getDimension()
{
	return vec2((float)width, (float)height);
}