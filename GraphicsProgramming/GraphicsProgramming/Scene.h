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
	GLuint Block;
	Disk Disk;
	Sphere Sphere;
	Cylinder Cylinder;
	Model My_model;

	int Seg = 1;
	float Size = 0.1;
	float ButtonMove = 0.005f;
	float TimePassed = 3.f;
	float ButtonTime = 0.3f;
	bool SphereBool = false;
	float CameraLoad = 0.5f;
	bool CameraTrue = false;


	//Lights 

	GLfloat Light_Ambient[4] = { 0.4f, 0.4f, 0.4f, 1.0f };
	GLfloat Light_Diffuse[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat Light_Position[4] = { -1.0f, 0.0f, 0.0f, 1.0f };
	GLfloat Spot_Direcion[3] = { 0.0f, -1.0f,0.0f };


	//Materials 
	GLfloat no_mat[4] = { 0.0, 0.0, 0.0, 0.0 };
	GLfloat mat_ambient_colour[4] = { 0.8, 0.8, 0.2, 1.0 };
	GLfloat mat_diff_red[4] = { 1.0, 0.0, 0.0, 1.0 };
	GLfloat mat_diff_blue[4] = { 0.1, 0.5, 0.8, 1.0 };
	GLfloat mat_specular[4] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat no_shininess = 0.0;
	GLfloat low_shininess = 50;
	GLfloat high_shininess = 100;
	GLfloat mat_emission[4] = { 0.3, 0.2, 0.2, 0.0 };




};

#endif