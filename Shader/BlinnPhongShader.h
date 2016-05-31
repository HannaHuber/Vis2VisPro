#pragma once

/** @file BlinnPhongShader.h
*@brief blinn phong shader class file.
*/

#include "Shader.h"
#include "PointLight.h"
#include <vector>
#include <memory>

/**  blinn phong shader.
  */
class BlinnPhongShader : public Shader {
public:
	/** Constructor.
	  * @param amb_col ambient color
	  * @param diff_col diffuse color
	  * @param spec_col specular color
	  * @param shin shininess
	  * @param transp transparency
	  */
	BlinnPhongShader(glm::vec3 amb_col, glm::vec3 diff_col, glm::vec3 spec_col, float shin, float transp);
	~BlinnPhongShader();

	/** Set point lights in shader. 
	  * @param allLights set of point lights
	  */
	virtual void setLighting(std::vector<std::shared_ptr<PointLight>> *allLights);

private:
	glm::vec3 ambient_color;
	glm::vec3 diffuse_color;
	glm::vec3 specular_color;
	float shininess;
	float transparency;

};