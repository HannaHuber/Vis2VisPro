#pragma once

#include "glm.hpp"
#include <list>
#include <vector>

#include "Shader.h"
#include "../VisPro/CutawaySurface.h"
#include "Face.h"
#include "BoundingBox.h"

class Mesh {
public:
	glm::mat4 model_matrix;

	// Constructor + destructor
	Mesh(std::vector<glm::vec3>& v, std::vector<glm::vec3>& n, std::vector<Face*>& f, std::vector<glm::vec2>& uv, Shader* shader ,glm::mat4& model_m); 
	virtual ~Mesh();

	// Update methods
	/** Update mesh according to time passed.
	* @param delta_t time passed since last update
	*/
	virtual void update(float delta_t);
	void rotateLocally(float delta_t, glm::vec3 axis);
	void rotateAroundCenter(glm::vec3& world_center, float angle, glm::vec3 axis);

	// Needed for Physics
	std::vector<glm::vec3> getNormals();
	std::vector<glm::vec3> getVertices();
	std::vector<GLuint> getIndices();

	// Z buffer pass methods
	/** Render depth values to z buffer.
	  * @param z z buffer shader
	  * @param vp view projection matrix
	  */
	void zBufferPass(ZBufferShader* z, glm::mat4& vp);
	
	/** Set model and view projection matrix in z buffer shader.
	  * @param z z buffer shader
	  * @param vp view projection matrix
	  */
	void setUniformsForZBufferPass(ZBufferShader* z, glm::mat4& vp);
	
	/** Actual OpenGL render call to draw elements to z buffer.
	  */
	void renderToZBuffer();

	// Render pass methods
	/** Render the given mesh (on screen). Clip against cutaway surface if wished.
	  * @param c cutaway surface
	  * @param vp view projection matrix
	  * @param cam camera position
	  * @param clip true to clip mesh against cutaway surface
	  */
	void renderPass(const CutawaySurface* c, glm::mat4& vp, glm::vec3 cam, float clip);

	/** Set model matrix, view projection matrix, camera position and clipping against cutaway surface in shader.
	  * @param vp view projection matrix
	  * @param cam camera position
	  * @param clip true to clip mesh against cutaway surface
	  */
	void setUniformsForRenderPass(glm::mat4& vp, glm::vec3 cam, float clip);
	
	/** Draw mesh triangles in current OpenGL context.
	  */
	virtual void draw();
		
	// Initial settings
	void setLighting(std::vector<std::shared_ptr<PointLight>> *allLights);
	void setCutawayDimension(glm::vec2 dim);
	void setShader(Shader* s);

	BoundingBox* calcBoundingBoxWithApplying();
	BoundingBox* calcBoundingBoxWithOutApplying();
	glm::vec3 getRelativePosition(glm::vec3 p);

	GLuint f_count; //number of faces
private:

	// Vertex data
	std::vector<glm::vec3> vertices;		// Vertex positions
	std::vector<glm::vec3> normals;			// Vertex normals
	std::vector<glm::vec2> uvs;				// Vertex uv coords
	std::vector<GLuint> indices;			// Vertex indices
	GLuint v_count, index_count;	// Counts

	// Faces
	const std::vector<Face*> faces; 		
	
	// Vertex buffer objects
	GLuint pos_vbo, normal_vbo, uv_vbo, index_vbo;

	// Vertex array object
	GLuint vao;

	// Shader
	Shader* shader;

	const float* Mesh::vec3ToFloatArray(std::list<glm::vec3*>& vectors);



};