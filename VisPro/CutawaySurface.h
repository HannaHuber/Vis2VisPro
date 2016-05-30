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
	/** Clear frame buffer object 1 and set appropriate OpenGL depth test.
	  */
	void prepareZBufferPass();
	/** Reset to default frame buffer object and appropriate OpenGL depth test.
	  */
	void endZBufferPass();
	/** Bind QuadShader to execute one round of jump flooding. 
	  * Switch between two frame buffer objects back and forth in every pass.
	  * @param step step size of current jump flooding iteration
	  * @param vp current view projection matrix
	  */
	void quadPass(int step, glm::mat4& vp);
	/** Prepare for rendering.
	  * Activate texture unit and choose right texture of frame buffer objects which is generated in last quad pass.
	  * @param unit texture unit to activate
	  */
	void prepareRenderPass(int unit);
	
	/** Dimension of cutaway surface plane in screen coordinates.
	 */
	glm::vec2 getDimension();
	
	/** Return texture handle according to index.
	  * @param tex texture index
	  * @return texture handle according to index
	  */
	GLuint getTextureHandle(int tex);

	/** Return frame buffer object handle according to index.
	* @param fbo frame buffer object index
	* @return frame buffer object handle according to index
	*/
	GLuint getFBOHandle(int fbo);

	void clearBuffers();
	
	ZBufferShader* z_buffer_shader;
	Quad* quad;
	QuadShader* quad_shader;

	float cut;
private:
	GLuint tex1, tex2, look_up_tex, target_tex, fbo1, fbo2, target_fbo;
	int width, height, last_target;
};