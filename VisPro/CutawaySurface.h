#pragma once

/** @file CutawaySurface.h
*@brief Cutaway surface class file.
*/

#include "ZBufferShader.h"
#include "Quad.h"
#include "QuadShader.h"
#include <memory>

/** Creation of cutaway surface and usage of resulting frame buffer objects or textures.  
  */
class CutawaySurface {
public: 
	CutawaySurface();
	~CutawaySurface();

	/** Init two frame buffer objects and attached textures and create z buffer shader and quad shader.
	  * @param w width of cutaway surface in screen coordinates
	  * @param h height of cutaway surface in screen coordinates
	  * @param z_near distance of near plane
	  * @param z_far distance of far plane
	  * @param angle drill angle of cutaway surface cones
	  * @param cut true if intersection with cutaway surfaces should be performed
	  */
	void init(int w, int h, float z_near, float z_far, float angle, float cut);

	/** Update z buffer shader and quad shader.
	* @param w width of cutaway surface in screen coordinates
	* @param h height of cutaway surface in screen coordinates
	* @param z_near distance of near plane
	* @param z_far distance of far plane
	* @param angle drill angle of cutaway surface cones
	* @param cut true if intersection with cutaway surfaces should be performed
	  */
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
	  * @return 2D vector of cutaway surface plane dimension
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

	/** Clear all used frame buffer objects and reset binding.
	  */
	void clearBuffers();
	
	/** Z buffer shader used for depth image calculation.
	  * Draws backfaces in depth image.
	  */
	ZBufferShader* z_buffer_shader;
	/** Quad used for neighbour coordinate interpolation.
	  */
	Quad* quad;
	/** Quad shader that implements the jump flood algorithm.
	  */
	QuadShader* quad_shader;
	/** Flag that defines if intersection with cutaway surface should be performed.
	*/
	float cut;
private:
	GLuint tex1, tex2, look_up_tex, target_tex, fbo1, fbo2, target_fbo;
	int width, height, last_target;
};