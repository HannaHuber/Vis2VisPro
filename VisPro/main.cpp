#pragma once

#include "main.h"

//// TCL integration
//#include <tk.h>
//#include "MyTkMain.h"
//
//// Standard
//#include <iostream>
//#include <fstream>
//#include <sstream>
//#include <stdio.h>
//#include <stdlib.h>
//
//// OpenGL extensions
//#include "glew.h"
//#include "glfw3.h"
//#include <GL/gl.h>
//#include "glm.hpp"
//#include "gtc/type_ptr.hpp"
//#include "gtc/matrix_transform.hpp"
//#include <memory>
//
//#include "UserInput.h"
//#include "Texture.h"
//#include "Geometry.h"
//#include "SceneObject.h"
//#include "PointLight.h"
//#include "Light.h"
//#include "../Scene/Camera.h"
//#include "../Shader/Shader.h"
//#include "../Shader/BlinnPhongShader.h"
//#include "../Shader/NormalShader.h"
//#include "../Shader/TextureShader.h"
//#include "SceneImporter.h"
//#include "SceneObjectManager.h"
//#include "CutawaySurface.h"
//#include "Quad.h"
//
//#include "StringHelpers.hpp"
//#include <opencv2\opencv.hpp>
//#include <opencv2\imgproc\imgproc.hpp>
//#include <opencv2\highgui\highgui.hpp>
//#include <opencv2\features2d\features2d.hpp>
//#include <opencv2\nonfree\features2d.hpp>
//#include <opencv2\highgui\highgui.hpp>
//#include <opencv2\nonfree\nonfree.hpp>
//
//#include <Windows.h> 
//#include <opencv2\highgui\highgui_c.h>
//#include "ZBufferView.h"
//#include "RGBBufferView.h"
//#include "TextureView.h"
//#include "FrameBufferObjectView.h"

using namespace std;
using namespace glm;

//// Default screen parameters
//int width = 1024;
//int height = 800;
//int refreshrate = 60;
//bool fullscreen = false;
//
//// Geometries
//SceneObjectManager obj_manager;
//vector<shared_ptr<Energy>> e_items;
//vector<shared_ptr<Environment>> environment;
//
//// Camera
//Camera* camera;
//float speed = 15.0f;
//float look_speed = 0.001f;
//float near_plane = 0.1f;
//float far_plane = 180.0f;
//float ratio = width / height;
//float fov = glm::radians(70.0f);
//
//// Distance transform
//CutawaySurface *cutaway = nullptr;
//float drill_angle = 40.0f; // glm::radians();
//float doCutaway = 1.0f;
//
//// Control
//UserInput user_input;
//
//// Number of culled faces
//int drawnFaces = 0;
//
//GLFWwindow* m_window = nullptr;
//
//std::string m_environmentDaeFile = "";
//std::string m_itemDaeFile = "";
//
//bool startSim = false;

// =============================================================================================
// TCL - Integration
// =============================================================================================

void UpdateNearPlane(float nearPlane)
{
	// update shader with current value
	near_plane = nearPlane;

	if (m_window != nullptr && cutaway != nullptr)
	{
		// Get actual window size
		glfwGetWindowSize(m_window, &width, &height);
		cutaway->update(width, height, near_plane, far_plane, drill_angle, doCutaway);
		camera->setProjMatrix(width, height, fov, far_plane, near_plane);
	}
}

void UpdateFarPlane(float farPlane)
{
	// update shader with current value
	far_plane = farPlane;

	if (m_window != nullptr && cutaway != nullptr)
	{
		// Get actual window size
		glfwGetWindowSize(m_window, &width, &height);
		cutaway->update(width, height, near_plane, far_plane, drill_angle, doCutaway);
		camera->setProjMatrix(width, height, fov, far_plane, near_plane);
	}
}

void UpdateDrillAngle(float drillAngle)
{
	// update shader with current value
	drill_angle = drillAngle; // glm::radians();

	if (m_window != nullptr && cutaway != nullptr)
	{
		// Get actual window size
		glfwGetWindowSize(m_window, &width, &height);
		cutaway->update(width, height, near_plane, far_plane, drill_angle, doCutaway);
	}
}

void UpdateEnvironment(const std::string &environmentDaeFile)
{
	// update environment dae file 
	m_environmentDaeFile = environmentDaeFile;
}

void UpdateItem(const std::string &itemDaeFile)
{
	// update item dae file 
	m_itemDaeFile = itemDaeFile;
}

int SetEnvironmentCmd(ClientData clientData, Tcl_Interp *interp,
	int argc, CONST84 char *argv[])
{	
	std::string envStr = argv[1];
	
	// check if file exists
	ifstream f(envStr.c_str());
	if (f.good())
	{
		UpdateEnvironment(envStr);
		return TCL_OK;
	}
	return TCL_ERROR;
}

int SetItemCmd(ClientData clientData, Tcl_Interp *interp,
	int argc, CONST84 char *argv[])
{
	std::string itemStr = argv[1];
	
	// check if file exists
	ifstream f(itemStr.c_str());
	if (f.good())
	{
		UpdateItem(itemStr);
		return TCL_OK;
	}
	return TCL_ERROR;
}

int StartSimCmd(ClientData clientData, Tcl_Interp *interp,
	int argc, CONST84 char *argv[])
{
	startSim = true;

	return TCL_OK;
}

int SetNearPlaneCmd(ClientData clientData, Tcl_Interp *interp,
	int argc, CONST84 char *argv[])
{
	double nearPlane = atof(argv[1]);
	if (nearPlane != 0)
		UpdateNearPlane(nearPlane);

	return TCL_OK;
}

int SetFarPlaneCmd(ClientData clientData, Tcl_Interp *interp,
	int argc, CONST84 char *argv[])
{
	double farPlane = atof(argv[1]);
	if (farPlane != 0)
		UpdateFarPlane(farPlane);

	return TCL_OK;
}

int SetDrillAngleCmd(ClientData clientData, Tcl_Interp *interp,
	int argc, CONST84 char *argv[])
{
	double drillAngle = atof(argv[1]);
	if (drillAngle != 0)
		UpdateDrillAngle(drillAngle);

	return TCL_OK;
}

int SetDoCutawayCmd(ClientData clientData, Tcl_Interp *interp,
	int argc, CONST84 char *argv[])
{
	int boolPtr[1];
	if (Tcl_GetBoolean(interp, argv[1], boolPtr) == TCL_OK)
	{
		doCutaway = *boolPtr;
		return TCL_OK;
	}

	return TCL_ERROR;
}

int GetNearPlaneCmd(ClientData clientData, Tcl_Interp *interp,
	int argc, CONST84 char *argv[])
{
	char buffer[20];
	sprintf_s(buffer, "%.2f", near_plane);
	Tcl_SetResult(interp, buffer, TCL_VOLATILE);
	return TCL_OK;
}

int GetFarPlaneCmd(ClientData clientData, Tcl_Interp *interp,
	int argc, CONST84 char *argv[])
{
	char buffer[20];
	sprintf_s(buffer, "%.2f", far_plane);
	Tcl_SetResult(interp, buffer, TCL_VOLATILE);
	return TCL_OK;
}

int GetDrillAngleCmd(ClientData clientData, Tcl_Interp *interp,
	int argc, CONST84 char *argv[])
{
	char buffer[20];
	sprintf_s(buffer, "%.2f", drill_angle);
	Tcl_SetResult(interp, buffer, TCL_VOLATILE);
	return TCL_OK;
}

int GetDoCutawayCmd(ClientData clientData, Tcl_Interp *interp,
	int argc, CONST84 char *argv[])
{
	char buffer[20];
	sprintf_s(buffer, "%1.0f", doCutaway);
	Tcl_SetResult(interp, buffer, TCL_VOLATILE);
	return TCL_OK;
}

int Tk_AppInit(Tcl_Interp *interp) {
	/*
	* Initialize packages
	*/
	if (Tcl_Init(interp) == TCL_ERROR) {
		return TCL_ERROR;
	}
	if (Tk_Init(interp) == TCL_ERROR) {
		return TCL_ERROR;
	}
	/*
	* Define application-specific commands here.
	*/
	Tcl_CreateCommand(interp, "setEnvironment", SetEnvironmentCmd,
		(ClientData)Tk_MainWindow(interp),
		(Tcl_CmdDeleteProc *)NULL);
	Tcl_CreateCommand(interp, "setItem", SetItemCmd,
		(ClientData)Tk_MainWindow(interp),
		(Tcl_CmdDeleteProc *)NULL);
	Tcl_CreateCommand(interp, "startSim", StartSimCmd,
		(ClientData)Tk_MainWindow(interp),
		(Tcl_CmdDeleteProc *)NULL);
	Tcl_CreateCommand(interp, "setNearPlane", SetNearPlaneCmd,
		(ClientData)Tk_MainWindow(interp),
		(Tcl_CmdDeleteProc *)NULL);
	Tcl_CreateCommand(interp, "setFarPlane", SetFarPlaneCmd,
		(ClientData)Tk_MainWindow(interp),
		(Tcl_CmdDeleteProc *)NULL);
	Tcl_CreateCommand(interp, "setDrillAngle", SetDrillAngleCmd,
		(ClientData)Tk_MainWindow(interp),
		(Tcl_CmdDeleteProc *)NULL);
	Tcl_CreateCommand(interp, "setDoCutaway", SetDoCutawayCmd,
		(ClientData)Tk_MainWindow(interp),
		(Tcl_CmdDeleteProc *)NULL);
	Tcl_CreateCommand(interp, "getNearPlane", GetNearPlaneCmd,
		(ClientData)Tk_MainWindow(interp),
		(Tcl_CmdDeleteProc *)NULL);
	Tcl_CreateCommand(interp, "getFarPlane", GetFarPlaneCmd,
		(ClientData)Tk_MainWindow(interp),
		(Tcl_CmdDeleteProc *)NULL);
	Tcl_CreateCommand(interp, "getDrillAngle", GetDrillAngleCmd,
		(ClientData)Tk_MainWindow(interp),
		(Tcl_CmdDeleteProc *)NULL);
	Tcl_CreateCommand(interp, "getDoCutaway", GetDoCutawayCmd,
		(ClientData)Tk_MainWindow(interp),
		(Tcl_CmdDeleteProc *)NULL);
	/*
	* Define start-up filename. This file is read in
	* case the program is run interactively.
	*/
	Tcl_SetVar(interp, "tcl_rcFileName", "~/.mytcl",
		TCL_GLOBAL_ONLY);
	return TCL_OK;
}

int InitTcl(int argc_in, char *argv_in[])
{

	int argc = argc_in;
	char **argv = argv_in;

	std::string guiScript;
	if (argc == 1)
	{
		// use VisPro.tcl as GUI
		std::string execPath = Helper::ExecutionPath();
		guiScript = execPath + "VisProGUI.tcl";

		argc++;
		argv = new char*[argc];

		argv[0] = argv_in[0];
		argv[1] = (char *) guiScript.c_str();
	}

	/*
	* Create an interpreter for the error message from
	* Tk_ParseArgv. Another one is created by Tk_Main.
	* Parse our arguments and leave the rest to Tk_Main.
	*/
	Tcl_FindExecutable(NULL);
	interp = Tcl_CreateInterp();
	if (Tk_ParseArgv(interp, (Tk_Window)NULL, &argc, (const char **) argv,
		argTable, 0) != TCL_OK) {
		fprintf(stderr, "%s\n", interp->resultDontUse);
		exit(1);
	}

	wchar_t **wargv = new wchar_t*[argc];
	for (int i = 0; i < argc; i++)
	{
		wchar_t *arg = Helper::convertCharArrayToLPCWSTR(argv[i]);
		wargv[i] = arg;
	}

	My_Tk_MainEx(argc, wargv, Tk_AppInit, interp);

	return TCL_OK;
}

void TearDownTcl() 
{ 
	My_TK_EndMainEx(interp);
}

int EvalTclFile(char *fileName)
{
	return Tcl_EvalFile(interp, fileName);
}

// =============================================================================================
// End TCL - Integration
// =============================================================================================

int main(int argc, char** argv) {	

	m_environmentDaeFile = "./Models/Japanese/japaneseHouse.dae";
	m_itemDaeFile = "./Models/Japanese/japaneseNoCarpet.dae";

	// Use input parameters
	initScreenParameters();

	InitTcl(argc, argv);

	// wait on start key
	while (!startSim)  {

		if (Tk_GetNumMainWindows() > 0) {
			Tcl_DoOneEvent(0);
		}
	}

	HWND tkWindow = GetActiveWindow();
	// -----------------------------------------------------------------------------------------
	// end of program initialization, start program
	// -----------------------------------------------------------------------------------------

	cutaway = new CutawaySurface();
	
	// Init GLFW
	if (!glfwInit()) {												// Init GLFW
		std::cout << "Failed to initialize GLFW\n" << std::endl;
		std::system("PAUSE");
		std::exit(-1);
	}
	
	// GLFW settings
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);					// OpenGL 4.0
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);	// Core profile
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);						// not resizable window	
	
	// Get monitor
	GLFWmonitor* monitor = nullptr;
	if (fullscreen) {
		monitor = glfwGetPrimaryMonitor();
		glfwWindowHint(GLFW_REFRESH_RATE, refreshrate);               
	}

	// Open window
	m_window = glfwCreateWindow(width, height, "Adaptive Cutaways", monitor, NULL); 
	if (m_window == NULL){
		std::cout << "Failed to open GLFW window." << std::endl;
		glfwTerminate();
		std::exit(-1);
	}

	// Init shader, scene objects and pipeline matrices
	init(m_window);

	// Init frametime
	float startTime = (float)glfwGetTime();
	float lastTime = (float)glfwGetTime();
	float deltaTime = 0;
	float time_used = 0;
	int frameCount = 0;

	// Init numbers for calculating fps
	int frames = 0;
	double lastReset = 0;
	double passedTimeSinceLastReset;
	double interval = 1; 
	int fps = 0;

	// Init
	ZBufferView zBufferView(width, height, "FBO1", cutaway->getFBOHandle(1));
	RGBBufferView rgbBufferView(width, height, "RGB");

	tex1View = new TextureView(width, height, "TEX1", Channels::RG_B, 0, cutaway->getTextureHandle(1));
	tex2View = new TextureView(width, height, "TEX2", Channels::RG_B, 0, cutaway->getTextureHandle(2));

	fbo101View = new FrameBufferObjectView(width, height, "after createDepthImage", Channels::RG_B, 1, 0, 1);
	fbo202View = new FrameBufferObjectView(width, height, "after createDepthImage", Channels::RG_B, 2, 0, 2);

	fbo101View_II = new FrameBufferObjectView(width, height, "after calculateCutawaySurface", Channels::RG_B, 1, 0, 1);
	fbo202View_II = new FrameBufferObjectView(width, height, "after calculateCutawaySurface", Channels::RG_B, 2, 0, 2);

	// Render loop running condition
	bool isRunning = true;
	std::cout << std::endl << "Renderloop is starting..." << std::endl;
	// ---------------------------------------------------------------------------------
	// --- RENDER LOOP ---
	// ---------------------------------------------------------------------------------
	while(isRunning)  { 

		// dispatch TCL-events for interpreter
		if (Tk_GetNumMainWindows() > 0) {
			Tcl_DoOneEvent(0);
		}

		if (freeMouse)
		{
			// free the mouse by window creation
			// ---------------------------------
			// Focus TCL window
			HWND currWindow = SetFocus(tkWindow);
			freeMouse = false;
		}

		// Calculate frametime
		deltaTime = (float)glfwGetTime()-lastTime;
		lastTime = (float)glfwGetTime();
	
		frameCount++;
		frames++;
		passedTimeSinceLastReset = glfwGetTime() - lastReset;
		if (passedTimeSinceLastReset >= interval){
			fps = frames / passedTimeSinceLastReset;
			lastReset = glfwGetTime();
			frames = 0;
		}

		// TEST
		cutaway->clearBuffers();

		// Update
		update(m_window, deltaTime);

		// Perform cutaway
		if (doCutaway)
		{
			// Init depth image
			createDepthImage();

			// check depth buffer here
			// write out z-Buffer as image or view with CodeXL
			// check fbo1 i.e. tex1 if depth image is written
			fbo101View->ShowBufferView(showZBufferView);
			//zBufferView.ShowBufferView(showZBufferView);
			//rgbBufferView.ShowBufferView(showZBufferView);
			if (updateZBufferView){
				fbo101View->UpdateBufferView();
				//zBufferView.UpdateBufferView();
				//rgbBufferView.UpdateBufferView();
			}

			// Compute cutaway surface
			calculateCutawaySurface();

			// check if fbo1 i.e. tex1 and fbo2 i.e. tex2 has depth values written
			fbo101View_II->ShowBufferView(showZBufferView);
			fbo202View_II->ShowBufferView(showZBufferView);
			if (updateZBufferView){
				fbo101View_II->UpdateBufferView();
				fbo202View_II->UpdateBufferView();
			}
			updateZBufferView = false;
		}
		
		// Draw 
		if (useWireFrame){											// Filled polygons/wireframe 
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		if (useTransparency) {										// Alpha blending
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}

		// Render scene
		draw();			
		
		// Disable wireframe
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 

		// Swap buffers
		glfwSwapBuffers(m_window);

		// Get window events
		glfwPollEvents();

		// Check for modi switches
		user_input.switchModi();
		
		// Check if the ESC key was pressed
		isRunning = (!user_input.terminate());
		
	} // -------------------------------------------------------------------------------------Render-Loop end

	// Framerate info
	std::cout << endl;
	std::cout << (frameCount / (glfwGetTime() - startTime)) << " fps (" << frameCount << " frames, " << (glfwGetTime() - startTime) << "s)" << std::endl;
	
	_sleep(4000);

	// Cleanup
	cleanup();

	// End GLFW
	glfwTerminate();

	TearDownTcl();
}

void init(GLFWwindow* window) {

	// Create OpenGL context
	glfwMakeContextCurrent(window);

	// Window title
	glfwSetWindowTitle(window, "Visualisierung 2");
	// Get actual window size
	glfwGetWindowSize(window, &width, &height);
	ratio = float(width) / height;

	// Init GLEW
	glewExperimental = true;										// Init GLEW
	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to initialize GLEW" << std::endl;
		std::exit(-1);
	}
	if (glewIsSupported("GL_VERSION_4_0")) {						// Check version support
		std::cout << "OpenGL version 4.0 supported" << endl;
	}

	// Init user input class
	user_input.init(window, false, true, true, 2, true, true, false, true);

	// Init opengl parameters	
	glClearColor(0.0, 0.0, 0.2, 0.5);						// Set backgroundcolor
	glViewport(0, 0, width, height);						// Viewport		

	if (useTransparency) {										// Alpha blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	// Visibility
	glEnable(GL_DEPTH_TEST);	// Depth test	
	glEnable(GL_CULL_FACE);		// Backface culling

	// Init scene importer
	SceneImporter s;
	s.setPrintInfo(false);
	std::vector<std::shared_ptr<PointLight>> allLights;
	std::shared_ptr<Camera> importedCamera; //TODO: not used yet

	// Import environmentH
	m_environmentDaeFile = Helper::AbsoluteFileName(m_environmentDaeFile);

	vector<shared_ptr<Geometry>> list = s.importFrom(m_environmentDaeFile, &allLights, importedCamera);

	for (int i = 0; i < list.size(); i++){
		shared_ptr<Environment> f = make_shared<Environment>(list[i]->model_matrix, list[i]->meshes);
		environment.push_back(f);
	}
	
	// Import energy
	m_itemDaeFile = Helper::AbsoluteFileName(m_itemDaeFile);

	list = s.importFrom(m_itemDaeFile, &allLights, importedCamera);

	for (int i = 0; i < list.size(); i++){
		shared_ptr<Energy> f = make_shared<Energy>(list[i]->model_matrix, list[i]->meshes, 20);
		e_items.push_back(f);
	}

	// Init camera
	mat4 model = rotate(translate(mat4(1.0f), vec3(40.0f, 5.0f, 5.0f)), 89.0f, vec3(0.0f,1.0f,0.0f));
	camera = new Camera(model);
	camera->setProjMatrix(width, height, fov, near_plane, far_plane);
	
	// Set objects
	obj_manager.setObjects(camera,
		&allLights,
		&environment,
		&e_items);
	
	// Distance transform
	cutaway->init(width, height, near_plane, far_plane, drill_angle, doCutaway);	


	// Lighting + cutaway dimensions
	vec2 dim = cutaway->getDimension();
	obj_manager.init(vec2((float) dim.x, (float) dim.y));
	
}

void update(GLFWwindow* window, float deltaTime) {

	// Camera
	vec3 direction = user_input.getMoveInput();
	camera->update(speed*deltaTime, direction);
	vec2 angle = user_input.getLookInput();
	camera->update(look_speed, angle);
	
	// Scene objects
	obj_manager.update(deltaTime);		

}

void createDepthImage() {
	cutaway->prepareZBufferPass();							
	obj_manager.renderToZBuffer(cutaway->z_buffer_shader, camera->proj_matrix*camera->view_matrix());
	cutaway->endZBufferPass();
}

void calculateCutawaySurface() {
	
	// Init step size with larger image dimension n
	int step = (width > height ? width / 2 : height / 2);

	// Iterate over window with changing step size k = n/2^i at the ith iteration 
	while (step > 0) {

		// Draw quad + calculate distance transform
		cutaway->quadPass(step, camera->proj_matrix);

		fbo101View->UpdateBufferView();
		cv::waitKey(1000);

		// Update step size for next iteration
		step /= 2;
		
	}

}

void draw() {	

	// Draw to screen
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, width, height);

	if (doCutaway)
		cutaway->prepareRenderPass(2);
	else
		cutaway->clearBuffers();

	// Render scene
	drawnFaces = obj_manager.draw(cutaway, useViewFrustumCulling);
}

void cleanup() {	
	delete camera;
	delete cutaway;
}

void initScreenParameters(){

	// Read from file
	std::string execPath = Helper::ExecutionPath();
	std::string settings_abs = execPath + "settings.txt";

	std::ifstream settingsFile(settings_abs);

	if (settingsFile.fail()){
		std::cout << "ERROR: Reading settingsfile failed! Using standard settings instead" << std::endl;
	}
	std::string type;
	int value;
	while (settingsFile >> type >> value){
		if (type == "width"){
			width = value;
		}
		else if (type == "height"){
			height = value;
		}
		else if (type == "angle"){
			drill_angle = (float)value; // glm::radians();
		}
		else if (type == "refreshrate"){
			refreshrate = value;			
		}
		else if (type == "fullscreen"){
			if (value == 0){
				fullscreen = false;
			}
			else if (value == 1){
				fullscreen = true;
			}
			else{
				std::cout << "WARNING: In settings.txt is a value that has not been processed because the value of fullscreen must be 0 or 1 but is " << value << std::endl;
			}
		}
		else if (type == "cutaway"){
			if (value == 0){
				doCutaway = false;
			}
			else if (value == 1){
				doCutaway = true;
			}
			else{
				std::cout << "WARNING: In settings.txt is a value that has not been processed because the value of fullscreen must be 0 or 1 but is " << value << std::endl;
			}
		}
		else{
			std::cout << "WARNING: In settings.txt is a value that has not been processed because it's unknown: " << type << std::endl;
		}
	}
	std::cout << "width=" << width << ", height=" << height << ", refreshrate=" << refreshrate << ", fullscreen=" << fullscreen << std::endl;

}
