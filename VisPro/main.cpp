#pragma once

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
//#include <boost_1_58_0/boost/gil/gil_all.hpp>
//#include "boost/gil/gil_all.hpp"
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


using namespace std;
using namespace glm;

void initScreenParameters();
void init(GLFWwindow* window);
void update(GLFWwindow* window,float deltaTime);
void createDepthImage();
void calculateCutawaySurface();
void draw(); 
void cleanup();

// Default screen parameters
int width = 1024;
int height = 800;
int refreshrate = 60;
bool fullscreen = false;

// Geometries
SceneObjectManager obj_manager;
vector<shared_ptr<Energy>> e_items;
vector<shared_ptr<Environment>> environment;

// Camera
Camera* camera;
float speed = 15.0f;
float look_speed = 0.001f;
float near_plane = 0.1;
float far_plane = 180.0;
float ratio = width / height;
float fov = glm::radians(70.0f);

// Distance transform
CutawaySurface cutaway;
float drill_angle = glm::radians(10.0f);

// Control
UserInput user_input;

// Number of culled faces
int drawnFaces = 0;

int main(int argc, char** argv) {	

	// Use input parameters
	initScreenParameters();
	
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
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);						// Resizable window	
	
	// Get monitor
	GLFWmonitor* monitor = nullptr;
	if (fullscreen) {
		monitor = glfwGetPrimaryMonitor();
		glfwWindowHint(GLFW_REFRESH_RATE, refreshrate);               
	}

	// Open window
	GLFWwindow* window = glfwCreateWindow(width, height, "ExtremelyCrazyTuStress", monitor, NULL); 
	if (window == NULL){
		std::cout << "Failed to open GLFW window." << std::endl;
		glfwTerminate();
		std::exit(-1);
	}

	// Init shader, scene objects and pipeline matrices
	init(window);

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
	ZBufferView zBufferView(width, height, cutaway.getFBOHandle(1));
	RGBBufferView rgbBufferView(width, height);
	TextureView tex1View(width, height, 0, cutaway.getTextureHandle(1));
	TextureView tex2View(width, height, 0, cutaway.getTextureHandle(2));
	/*TextureView tex3View(width, height, 2, cutaway.getTextureHandle(1));
	TextureView tex4View(width, height, 2, cutaway.getTextureHandle(2));*/
	/*FrameBufferObjectView fbo101View(width, height, 1, 0, 1);
	FrameBufferObjectView fbo102View(width, height, 1, 0, 2);
	FrameBufferObjectView fbo121View(width, height, 1, 2, 1);
	FrameBufferObjectView fbo122View(width, height, 1, 2, 2);
	FrameBufferObjectView fbo201View(width, height, 2, 0, 1);
	FrameBufferObjectView fbo202View(width, height, 2, 0, 2);
	FrameBufferObjectView fbo221View(width, height, 2, 2, 1);
	FrameBufferObjectView fbo222View(width, height, 2, 2, 2);*/


	// Render loop running condition
	bool isRunning = true;
	std::cout << std::endl << "Renderloop is starting..." << std::endl;
	// ---------------------------------------------------------------------------------
	// --- RENDER LOOP ---
	// ---------------------------------------------------------------------------------
	while(isRunning)  { 

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

		// Update
		update(window, deltaTime);

		// Init depth image
		createDepthImage();

		// TODO: check depth buffer here
		// write out z-Buffer as image or view with CodeXL

		zBufferView.ShowBufferView(showZBufferView);
		rgbBufferView.ShowBufferView(showZBufferView);
		if (updateZBufferView){
			zBufferView.UpdateBufferView();
			rgbBufferView.UpdateBufferView();
		}
		//updateZBufferView = false;

		// Compute cutaway surface
		calculateCutawaySurface();

		tex1View.ShowBufferView(showZBufferView); 
		tex2View.ShowBufferView(showZBufferView);
		/*tex3View.ShowBufferView(showZBufferView);
		tex4View.ShowBufferView(showZBufferView);*/
		/*fbo101View.ShowBufferView(showZBufferView);
		fbo102View.ShowBufferView(showZBufferView);
		fbo121View.ShowBufferView(showZBufferView);
		fbo122View.ShowBufferView(showZBufferView);
		fbo201View.ShowBufferView(showZBufferView);
		fbo202View.ShowBufferView(showZBufferView);
		fbo221View.ShowBufferView(showZBufferView);
		fbo222View.ShowBufferView(showZBufferView);*/
		if (updateZBufferView){
			tex1View.UpdateBufferView();
			tex2View.UpdateBufferView();
			/*tex3View.UpdateBufferView();
			tex4View.UpdateBufferView();*/
			/*fbo101View.UpdateBufferView();
			fbo102View.UpdateBufferView();
			fbo121View.UpdateBufferView();
			fbo122View.UpdateBufferView();
			fbo201View.UpdateBufferView();
			fbo202View.UpdateBufferView();
			fbo221View.UpdateBufferView();
			fbo222View.UpdateBufferView();*/
		}
		updateZBufferView = false;

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
		glfwSwapBuffers(window);

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

	std::system("PAUSE");

	std::exit(0);
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

	// Import environment
	vector<shared_ptr<Geometry>> list = s.importFrom("../Models/Villa/villaLayer.dae", &allLights, importedCamera);
	for (int i = 0; i < list.size(); i++){
		shared_ptr<Environment> f = make_shared<Environment>(list[i]->model_matrix, list[i]->meshes);
		environment.push_back(f);
	}
	
	// Import energy
	list = s.importFrom("../Models/Villa/stoolLayer.dae", &allLights, importedCamera);
	for (int i = 0; i < list.size(); i++){
		shared_ptr<Energy> f = make_shared<Energy>(list[i]->model_matrix, list[i]->meshes, 20);
		e_items.push_back(f);
	}

	// Init camera
	mat4 model = translate(mat4(1.0), vec3(20.0, 10.0, -20));
	camera = new Camera(model);
	camera->setProjMatrix(width, height, fov, near_plane, far_plane);
	
	// Set objects
	obj_manager.setObjects(camera,
		&allLights,
		&environment,
		&e_items);
	
	// Lighting
	obj_manager.setLighting();

	// Distance transform
	cutaway.init(width, height, near_plane, far_plane, drill_angle);	
	
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
	cutaway.prepareZBufferPass();							
	obj_manager.renderToZBuffer(cutaway.z_buffer_shader, camera->proj_matrix*camera->view_matrix());
	cutaway.endZBufferPass();
}

void calculateCutawaySurface() {
	
	// Init step size with larger image dimension n
	int step = (width > height ? width / 2 : height / 2);

	// Iterate over window with changing step size k = n/2^i at the ith iteration 
	while (step > 0) {

		// Draw quad + calculate distance transform
		cutaway.quadPass(step, camera->proj_matrix * camera->view_matrix());

		// Update step size for next iteration
		step /= 2;
	}

}

void draw() {	

	// Draw to screen
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClearColor(0.0f, 0.0f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, width, height);

	cutaway.prepareRenderPass(2);

	// Render scene
	drawnFaces = obj_manager.draw(&cutaway, useViewFrustumCulling);
}

void cleanup() {	
	delete camera;
}

void initScreenParameters(){

	// Read from file
//#ifdef _DEBUG
	std::string execPath = Helper::ExecutionPath();
	std::string settings_abs = execPath + "settings.txt";

	std::ifstream settingsFile(settings_abs);
//#else
//	std::ifstream settingsFile("./settings.txt");
//#endif

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
		else{
			std::cout << "WARNING: In settings.txt is a value that has not been processed because it's unknown: " << type << std::endl;
		}
	}
	std::cout << "width=" << width << ", height=" << height << ", refreshrate=" << refreshrate << ", fullscreen=" << fullscreen << std::endl;

}



