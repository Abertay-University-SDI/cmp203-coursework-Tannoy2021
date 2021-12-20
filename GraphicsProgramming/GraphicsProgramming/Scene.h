// Scene class. Configures a basic 3D scene.
// Interfaces with the Input class to handle user input
// Calculates and outputs Frames Per Second (FPS) rendered.
// Important functions are the constructor (initialising the scene), 
// update (for process user input and updating scene objects) and render (renders scene).
#ifndef _SCENE_H
#define _SCENE_H

// Include GLUT, openGL, input.
#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Input.h"
#include <stdio.h>
// Further includes should go here:
#include "SOIL.h"
#include <vector>
#include "Shadow.h"
#include "Camera.h"
#include "Disk.h"
#include "Sphere.h"
#include "Cylinder.h"
#include "Model.h"


class Scene{

public:
	Scene(Input *in);
	// Main render function
	void render();
	// Handle input function that receives delta time from parent.
	void handleInput(float dt,Input* in);
	// Update function receives delta time from parent (used for frame independent updating).
	void update(float dt);
	// Resizes the OpenGL output based on new window size.
	void resize(int w, int h);

protected:
	// configure opengl render pipeline
	void initialiseOpenGL();
	// Renders text (x, y positions, RGB colour of text, string of text to be rendered)
	void displayText(float x, float y, float r, float g, float b, char* string);
	// A function to collate all text output in a single location
	void renderTextOutput();
	void calculateFPS();

	// draw primitive functions
	
	void drawCube();

	// For access to user input.
	Input* input;
		
	// For Window and frustum calculation.
	int width, height;
	float fov, nearPlane, farPlane;

	// For FPS counter and mouse coordinate output.
	int frame = 0, time, timebase = 0;
	char fps[40];
	char mouseText[40];

	Camera Camera;
	GLuint Crate;
	GLuint Grass;
	GLuint Skybox;
	GLuint Block;
	GLuint Sun;
	Shadow Shadows;
	
	Disk Disk;
	Sphere Sphere;
	Cylinder Cylinder;
	Model My_model;
	Model Torch;

	int Seg = 1;
	float Size = 0.15;
	float ButtonMove = 0.005f;
	float TimePassed = 3.f;
	float ButtonTime = 0.3f;
	bool SphereBool = false;
	float CameraLoad = 0.5f;
	bool CameraTrue = false;
	bool EnableWireframe = false;
	float rotation = 0;


	// These 3 floats are used for rendering a sphere inside the metal torch
	// this way the sphere is fit perfectly 
	float TorchX = -0.37f;
	float TorchY = 0.6f;
	float TorchZ = -0.37;

	bool FirstPerson = false;

	//Sun floats
	float SunX = 50.f;
	float SunZ = 4.f;



	//Lights 
	// 	// The possitions are inverted
	// a 1 will shine in the negative direction
	// while -1 will shine in the possitive direction
	// // The last value is called W 
	// if its 0 its a directional light 
	// if its 1 the light starts from the possition 
	// 



	// Sun light set up
	GLfloat Light_Ambient3[4] = { 0.4f, 0.4f, 0.4f, 1.0f };
	GLfloat Light_Position3[4] = { 3.57,-3,SunZ, 1.0f };

	//
	// booleans and GLfloats to set the ambient light to Yellow red or blue
	bool Yellow = true;
	bool Red = false;
	bool Green = false;
	bool Dull = false;


	GLfloat Red_Ambient[4] = { 0.9f,0.0f,0.9f,1.0f };
	GLfloat Green_Ambient[4] = { 0.2f,0.9f,0.9f,1.0f };
	GLfloat Dull_Ambient[4] = { 0.2f,0.2f,0.9f,1.0f };
	// 
	//Torch Lights 
	// Torches on the Left wall 
	GLfloat Light_Ambient[4] = { 0.9f, 0.9f, 0.9f, 1.0f };
	GLfloat Light_Diffuse[4] = { 0.4f, 0.4f, 0.4f, 1.0f };
	GLfloat Light_Position[4] = { -2.87f, -1.7f, 4.f, 1.0f };
	GLfloat Spot_Direcion[3] = { 0.1f, 1.0f,0.0f };

	/*GLfloat Light_Ambient1[4] = { 0.9f, 0.9f, 0.9f, 1.0f };
	GLfloat Light_Diffuse1[4] = { 1.f, 1.f, 1.f, 1.0f };
	GLfloat Light_Position1[4] = { -2.87f, -1.7f, 2.f, 1.0f };
	GLfloat Spot_Direcion1[3] = { -0.0f, 1.0f,0.0f };*/

	// Torches on the right wall

	GLfloat Light_Ambient2[4] = { 0.9f, 0.9f, 0.9f, 1.0f };
	GLfloat Light_Diffuse2[4] = { 0.4f, 0.4f, 0.4f, 1.0f };
	GLfloat Light_Position2[4] = { 10.87f, -1.2f, 4.f, 1.0f };
	GLfloat Spot_Direcion2[3] = { -0.2f, 1.0f,0.0f };



	// Torches on the front wall 

	GLfloat Light_Ambient4[4] = { 0.9f, 0.9f, 0.9f, 1.0f };
	GLfloat Light_Diffuse4[4] = { 0.4f, 0.4f, 0.4f, 1.0f };
	GLfloat Light_Position4[4] = { 3.57f, -1.7f, 8.f, 1.0f };
	GLfloat Spot_Direcion4[3] = { 0.0f, 1.0f,-0.2f };

	GLfloat Light_Ambient5[4] = { 0.9f, 0.9f, 0.9f, 1.0f };
	GLfloat Light_Diffuse5[4] = { 0.4f, 0.4f, 0.4f, 1.0f };
	GLfloat Light_Position5[4] = { 6.57f, -1.7f, 8.f, 1.0f };
	GLfloat Spot_Direcion5[3] = { 0.0f, 1.0f,-0.2f };

	// Torches on the back wall

	GLfloat Light_Ambient6[4] = { 0.9f, 0.9f, 0.9f, 1.0f };
	GLfloat Light_Diffuse6[4] = { 0.4f, 0.4f, 0.4f, 1.0f };
	GLfloat Light_Position6[4] = { 3.57f, -1.7f, 0.f, 1.0f };
	GLfloat Spot_Direcion6[3] = { 0.0f, 1.0f,0.2f };

	GLfloat Light_Ambient7[4] = { 0.9f, 0.9f, 0.9f, 1.0f };
	GLfloat Light_Diffuse7[4] = { 0.4f, 0.4f, 0.4f, 1.0f };
	GLfloat Light_Position7[4] = { 7.57f, -1.7f, 0.f, 1.0f };
	GLfloat Spot_Direcion7[3] = { 0.0f, 1.0f,0.2f };


	//Materials 
	GLfloat no_mat[4] = { 0.0, 0.0, 0.0, 0.0 };
	GLfloat mat_ambient_colour[4] = { 0.8,0.8,0.2, 1.0 };
	GLfloat mat_diff_red[4] = { 1.0, 0.0, 0.0, 1.0 };
	GLfloat mat_diff_blue[4] = { 0.1, 0.5, 0.8, 1.0 };
	GLfloat mat_specular[4] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat no_shininess = 0.0;
	GLfloat low_shininess = 50;
	GLfloat high_shininess = 100;
	GLfloat mat_emission[4] = { 0.0, 0.0, 0.0, 0.0 };



};

#endif