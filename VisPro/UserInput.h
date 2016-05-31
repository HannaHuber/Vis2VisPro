#pragma once

/** @file UserInput.h
*@brief User input class file.
*/

#include <iostream>
#include "glfw3.h"
#include "glm.hpp"

/** User input class. 
  */
class UserInput
{
public:
	UserInput(GLFWwindow* window);
	UserInput();
	~UserInput();

	void init(GLFWwindow* window, bool wire, bool frame, bool lin_tex, int mip, bool vf_cull, bool transp, bool bloom, bool count_down);
	bool terminate();

	// Player related input
	glm::vec3 getMoveInput();
	glm::vec2 getLookInput();
	bool getFireInput();
	
	void switchModi();

private:
	GLFWwindow* window;
	glm::vec2 screen_center;
	
	float lastButtonPress = 0; //extra buttons (F2,F3,...)
	float minDist = 0.4; //minimum 0.4 seconds between 2 button presses
		
	// Extras
	void switchFrameTimeMode();
	void switchWireFrameMode();
	void switchTexSamplingMode();
	void switchMipMapMode();
	void switchViewFrustumCullingMode();
	void switchTransparencyMode();
	void switchBloomMode();
	void switchCountdownMode();

	/** Trigger opening of view of diverse OpenGL buffers of Open GL. 
	  */
	void toggleShowZBufferView();

	/** Trigger update of view of diverse OpenGL buffers of Open GL.
	*/
	void toggleUpdateZBufferView();

	/** Free the mouse from sticky GLWF window. 
	  */
	void doFreeMouse();

};

//global
extern bool showFrameTime, useWireFrame, useLinearTexSampling, useViewFrustumCulling, useTransparency, useBloom, countDown, showZBufferView, updateZBufferView, freeMouse;
extern int useMipMapping; // 0: off, 1: nearest neighbour, 2: linear

