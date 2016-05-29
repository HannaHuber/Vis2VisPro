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
	virtual void update(float deltaTime);
	int Geometry::draw(const CutawaySurface* c, ViewFrustum& frust, glm::mat4& vp, glm::vec3 cam, bool useViewFrustumCulling, bool clip);
	void draw();
	virtual void addChild(Geometry* g);
	virtual void setShader(Shader* shader);
	virtual void transformModelMatrix(glm::mat4& transform );
	virtual void init(std::vector<std::shared_ptr<PointLight>> *allLights, glm::vec2 dim);
	virtual void setViewProj(glm::mat4& vpm);
	virtual void setCameraLoc(glm::vec3 loc);
	virtual void renderToZBuffer(ZBufferShader* z, glm::mat4& vp);
	std::vector<Mesh*> meshes;
	std::vector<glm::vec3> relativeMeshPositions;
	int faceCount =0; //number of faces in this Geometry
private:

	BoundingBox* b; 

	
};

