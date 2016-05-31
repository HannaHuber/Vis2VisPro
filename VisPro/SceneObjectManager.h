#pragma once

/** @file SceneObjectManager.h
*@brief scene object manager class file.
*/

#include "PointLight.h"
#include "Camera.h"
#include "Environment.h"
#include "Energy.h"
#include "UserInput.h"

/** Manges scene objects of simulation. 
  */
class SceneObjectManager {
public:
	SceneObjectManager();
	~SceneObjectManager();
	void setObjects(Camera* c,
					std::vector<std::shared_ptr<PointLight>>* l, 
					std::vector<std::shared_ptr<Environment>>* e, 
					std::vector<std::shared_ptr<Energy>>* e_i);
	void init(glm::vec2 dim);
	
	/** Update all scene objects according to time passed.
	  * @param delta_t time passed since last update
	  */
	void update(float delta_t);

	/** Render scene objects to given z buffer.
	  * @param z z buffer shader
	  * @param vp view projection matrix
	  */
	void renderToZBuffer(ZBufferShader* z, glm::mat4& vp);

	/** Draw scene objects (on screen) using given cutaway surface.
	  * Objects of interest are drawn fully whereas secondary objects are intersected with cutaway surface.
	  * @param sm cutaway surface
	  * @param useViewFrustumCulling true to use view frustum culling
	  * @return number of drawn faces
	  */
	int draw(const CutawaySurface* sm, bool useViewFrustumCulling);

private:
	std::vector<std::shared_ptr<PointLight>>* lights;
	Camera* camera;
	std::vector<std::shared_ptr<Environment>>* environment;
	std::vector<std::shared_ptr<Energy>>* e_items;
	ViewFrustum frustum = ViewFrustum();
	

};
