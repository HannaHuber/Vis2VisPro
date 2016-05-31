#pragma once

#include "SceneObject.h"
#include "Mesh.h"
#include "../VisPro/CutawaySurface.h"
#include <vector>
#include <memory>
#include "../VisPro/ViewFrustum.h"

class Geometry : public SceneObject{
public:
	Geometry(glm::mat4& model_matrix, std::vector<Mesh*> m);
	virtual ~Geometry();

	/** Update contained geometry (collection of meshes) according to time passed.
	  * @param deltaTime time passed since last update
	  */
	virtual void update(float deltaTime);

	/** Draws contained geometry (collection of meshes) (on screen).
	 * Intersect geometry with given cutaway surface.
	 * @param c cutaway surface
	 * @param frust view frustum
	 * @param vp view projection matrix
	 * @param cam camera position
	 * @param useViewFrustumCulling true to use view frustum culling
	 * @param clip true to clip against cutaway surface
	*/
	int draw(const CutawaySurface* c, ViewFrustum& frust, glm::mat4& vp, glm::vec3 cam, bool useViewFrustumCulling, float clip);
	void draw();
	virtual void addChild(Geometry* g);
	virtual void setShader(Shader* shader);
	virtual void transformModelMatrix(glm::mat4& transform );
	virtual void init(std::vector<std::shared_ptr<PointLight>> *allLights, glm::vec2 dim);
	virtual void setViewProj(glm::mat4& vpm);
	virtual void setCameraLoc(glm::vec3 loc);
	/** Render contained geometry (collection of meshes) to z buffer.
	  * @param z z buffer shader
	  * @param vp view projection matrix
	  */
	virtual void renderToZBuffer(ZBufferShader* z, glm::mat4& vp);
	std::vector<Mesh*> meshes;
	std::vector<glm::vec3> relativeMeshPositions;
	int faceCount =0; //number of faces in this Geometry
private:

	BoundingBox* b; 

	
};

