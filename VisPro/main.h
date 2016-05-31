#pragma once

/** @file main.h 
  *@brief main application file
  */

// TCL integration
#include <tk.h>
#include "MyTkMain.h"

// Standard
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>

// OpenGL extensions
#include "glew.h"
#include "glfw3.h"
#include <GL/gl.h>
#include "glm.hpp"
#include "gtc/type_ptr.hpp"
#include "gtc/matrix_transform.hpp"
#include <memory>

#include "UserInput.h"
#include "Texture.h"
#include "Geometry.h"
#include "SceneObject.h"
#include "PointLight.h"
#include "Light.h"
#include "../Scene/Camera.h"
#include "../Shader/Shader.h"
#include "../Shader/BlinnPhongShader.h"
#include "../Shader/NormalShader.h"
#include "../Shader/TextureShader.h"
#include "SceneImporter.h"
#include "SceneObjectManager.h"
#include "CutawaySurface.h"
#include "Quad.h"

#include "StringHelpers.hpp"
#include <opencv2\opencv.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\features2d\features2d.hpp>
#include <opencv2\nonfree\features2d.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\nonfree\nonfree.hpp>

#include <Windows.h> 
#include <opencv2\highgui\highgui_c.h>
#include "ZBufferView.h"
#include "RGBBufferView.h"
#include "TextureView.h"
#include "FrameBufferObjectView.h"


// Default screen parameters
int width = 1024;
int height = 800;
int refreshrate = 60;
bool fullscreen = false;

// Geometries
SceneObjectManager obj_manager;
std::vector<std::shared_ptr<Energy>> e_items;
std::vector<std::shared_ptr<Environment>> environment;

// Camera
Camera* camera;
float speed = 15.0f;
float look_speed = 0.001f;
float near_plane = 0.1f;
float far_plane = 180.0f;
float ratio = width / height;
float fov = glm::radians(70.0f);

// Distance transform
CutawaySurface *cutaway = nullptr;
float drill_angle = 40.0f; // glm::radians();
float doCutaway = 1.0f;

// Control
UserInput user_input;

// Number of culled faces
int drawnFaces = 0;

GLFWwindow* m_window = nullptr;

std::string m_environmentDaeFile = "";
std::string m_itemDaeFile = "";

ZBufferView *zBufferView = nullptr;
RGBBufferView *rgbBufferView = nullptr;

TextureView *tex1View = nullptr;
TextureView *tex2View = nullptr;

FrameBufferObjectView *fbo101View = nullptr;
FrameBufferObjectView *fbo202View = nullptr;

FrameBufferObjectView *fbo101View_II = nullptr;
FrameBufferObjectView *fbo202View_II = nullptr;


// =============================================================================================
// TCL - Integration
// =============================================================================================

bool startSim = false;

// TCL components for GUI
Tcl_Interp *interp = nullptr;
static Tk_ArgvInfo argTable[] = { { "", TK_ARGV_END } };

/** Update near plane in OpenGL view.
* @param nearPlane distance of near plane
*/
void UpdateNearPlane(float nearPlane);

/** Update far plane in OpenGL view.
* @param farPlane distance of far plane
*/
void UpdateFarPlane(float farPlane);

/** Update drill angle for cutaway surface calculation.
* @param drillAngle angle that defines the steepness of cutting cones
*/
void UpdateDrillAngle(float drillAngle);

/** Update secondary objects i.e. environment file in simulation.
* @param environmentDaeFile dae file of secondary objects i.e. environment
*/
void UpdateEnvironment(const std::string &environmentDaeFile);

/** Update primary objects i.e. items file in simulation.
* @param itemDaeFile dae file of primary objects i.e. items
*/
void UpdateItem(const std::string &itemDaeFile);

/** TCL command function to set secondary objects i.e. environment file in simulation.
* @param clientData data handle to interpreter values
* @param interp current TCL interpreter
* @param argc number of arguments to TCL command
* @param argv arguments to TCL command as string array
*/
int SetEnvironmentCmd(ClientData clientData, Tcl_Interp *interp,
	int argc, CONST84 char *argv[]);

/** TCL command function to set primary objects i.e. item file in simulation.
* @param clientData data handle to interpreter values
* @param interp current TCL interpreter
* @param argc number of arguments to TCL command
* @param argv arguments to TCL command as string array
*/
int SetItemCmd(ClientData clientData, Tcl_Interp *interp,
	int argc, CONST84 char *argv[]);

/** TCL command function to switch from initialization mode of the simulation to running mode.
* @param clientData data handle to interpreter values
* @param interp current TCL interpreter
* @param argc number of arguments to TCL command
* @param argv arguments to TCL command as string array
*/
int StartSimCmd(ClientData clientData, Tcl_Interp *interp,
	int argc, CONST84 char *argv[]);

/** TCL command function to  set the near plane in OpenGL view.
* @param clientData data handle to interpreter values
* @param interp current TCL interpreter
* @param argc number of arguments to TCL command
* @param argv arguments to TCL command as string array
*/
int SetNearPlaneCmd(ClientData clientData, Tcl_Interp *interp,
	int argc, CONST84 char *argv[]);

/** TCL command function to  set the far plane in OpenGL view.
* @param clientData data handle to interpreter values
* @param interp current TCL interpreter
* @param argc number of arguments to TCL command
* @param argv arguments to TCL command as string array
*/
int SetFarPlaneCmd(ClientData clientData, Tcl_Interp *interp,
	int argc, CONST84 char *argv[]);

/** TCL command function to set drill angle for cutaway surface calculation.
* @param clientData data handle to interpreter values
* @param interp current TCL interpreter
* @param argc number of arguments to TCL command
* @param argv arguments to TCL command as string array
*/
int SetDrillAngleCmd(ClientData clientData, Tcl_Interp *interp,
	int argc, CONST84 char *argv[]);

/** TCL command function to enable or disable cutaway surface calculation.
* @param clientData data handle to interpreter values
* @param interp current TCL interpreter
* @param argc number of arguments to TCL command
* @param argv arguments to TCL command as string array
*/
int SetDoCutawayCmd(ClientData clientData, Tcl_Interp *interp,
	int argc, CONST84 char *argv[]);

/** TCL command function to return the near plane distance value of OpenGL view to TCL script.
* @param clientData data handle to interpreter values
* @param interp current TCL interpreter
* @param argc number of arguments to TCL command
* @param argv arguments to TCL command as string array
*/
int GetNearPlaneCmd(ClientData clientData, Tcl_Interp *interp,
	int argc, CONST84 char *argv[]);

/** TCL command function to return the far plane distance value of OpenGL view to TCL script.
* @param clientData data handle to interpreter values
* @param interp current TCL interpreter
* @param argc number of arguments to TCL command
* @param argv arguments to TCL command as string array
*/
int GetFarPlaneCmd(ClientData clientData, Tcl_Interp *interp,
	int argc, CONST84 char *argv[]);

/** TCL command function to return the drill angle of cutaway surface calculation to TCL script.
* @param clientData data handle to interpreter values
* @param interp current TCL interpreter
* @param argc number of arguments to TCL command
* @param argv arguments to TCL command as string array
*/
int GetDrillAngleCmd(ClientData clientData, Tcl_Interp *interp,
	int argc, CONST84 char *argv[]);

/** TCL command function to return cutaway surface flag to TCL script.
* @param clientData data handle to interpreter values
* @param interp current TCL interpreter
* @param argc number of arguments to TCL command
* @param argv arguments to TCL command as string array
*/
int GetDoCutawayCmd(ClientData clientData, Tcl_Interp *interp,
	int argc, CONST84 char *argv[]);

/** Tk application initializer.
* Define application-specific commands here.
* @param interp current TCL interpreter
* @return TCL_OK if everything is fine
*/
int Tk_AppInit(Tcl_Interp *interp);

/** Initialization of TCL interpreter.
* Create an interpreter here.
* @param argc_in pendant to application argc
* @param argv_in pendant to application argv
* @return TCL_OK if everything is fine
*/
int InitTcl(int argc_in, char *argv_in[]);

/** Tear down TCL interpreter and application.
*/
void TearDownTcl();

/** Eval given TCL script in current interpreter.
* @param fileName filename of TCL script
* @return TCL_OK if everything is fine, TCL_ERROR otherwise
*/
int EvalTclFile(char *fileName);

// =============================================================================================
// End TCL - Integration
// =============================================================================================

// =============================================================================================
// main application
// =============================================================================================

/** Main entry point of application
* @param argc number of command line arguments
* @param argv command line arguments within a string array
* @return 0 if everything is OK
*/
int main(int argc, char** argv);

/** Initialization of GLFW window as main render context, loading of objects of interest and secondary objects, setup of view in the simulation.
* Initialization of cutaway surface calculation is also done here.
* @param window the GLFW window to bind
*/
void init(GLFWwindow* window);

/** Update of view of given GLFW window.
* Update camera as well as scene according to time passed since last update.
* @param window given GLFW window
* @param deltaTime time since last update
*/
void update(GLFWwindow* window, float deltaTime);

/** Creation of depth image of objects of interest.
* The depth image is a starting point of cutaway calculation.
*/
void createDepthImage();

/** Calculate the cutaway surface out of depth values of objects of interest.
* Process is iterative. Several passes of jump flooding algorithm with decreasing step size are triggered here.
*/
void calculateCutawaySurface();

/** Draw objects of interest and secondary objects.
* Objects of interest are drawn completely whereas secondary objects are intersected with the cutaway surface.
*/
void draw();

/** Cleanup of simulation objects.
*/
void cleanup();

/** Extraction of simulation parameters for screen and cutaway surface calculation from settings file.
*/
void initScreenParameters();

// =============================================================================================
//  End main application
// =============================================================================================

