// as seen in CG Tutorial (http://cg.tuwien.ac.at/courses/CG23/videos/2015/CG_Tut_2_part4%20-%20WLAN.m4v)

#pragma once

#include <string>
#include "glew.h"
#include "glfw3.h"
#include "../Scene/PointLight.h"
#include <vector>
#include <memory>

/** Shader base class.
  */
class Shader
{
public:
	Shader(const std::string& vertexShader, const std::string& fragmentShader);
	Shader(const std::string& vertexShader, const std::string& geometryShader, const std::string& fragmentShader);
	~Shader();

	/** Installs given GLSL program.
	  */
	void useShader() const;
	
	/** Install shader and set lighting.
	* @param allLights set of given point lights
	*/
	virtual void setLighting(std::vector<std::shared_ptr<PointLight>> *allLights);
	
	/** Set screen coordinate dimension of cutaway surface plane in shader.
	  * @param dim 2D vector of cutaway surface plane dimension
	  */
	void setCutawayDimension(glm::vec2 dim);

	/** Bind given texture unit in given context.
	* @param unit texture unit identifier
	*/
	virtual void bindTexture(int unit);

	GLuint programHandle;

private:
	/** Verify and compile shader.
	  * @param shader file
	  * @param shaderType type of shader (vertex, fragment, geometry)
	  * @param handle handle to compiled shader
	  */
	void loadShader(const std::string& shader, GLenum shaderType, GLuint& handle);
	/** Attach and link the compiled vertex and fragment shader to program.
	  */
	void link();
	/** Attach and link the compiled vertex, geometry and fragment shader to program.
	  */
	void linkWithGeometryShader();

	GLuint vertexHandle;
	GLuint fragmentHandle;
	GLuint geometryHandle;
};