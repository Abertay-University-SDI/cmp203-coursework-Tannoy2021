#include "Scene.h"

// Scene constructor, initilises OpenGL
// You should add further variables to need initilised.
Scene::Scene(Input *in)
{
	// Store pointer for input class
	input = in;
	initialiseOpenGL();

	// Other OpenGL / render setting should be applied here.
	if (!My_model.load("models/breakables_ground.obj", "models/breakables_ground_c.png"))
	{
		printf(" uh oh pee pee poo poo");
	}


	Grass = SOIL_load_OGL_texture("gfx/checked.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	Crate = SOIL_load_OGL_texture("gfx/crate.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	Block = SOIL_load_OGL_texture("models/breakables_ground_c.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	glTexEnvf(GL_TEXTURE, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	// Initialise scene variables
	/*Disk.Calculate(1, 50);*/
	
}

void Scene::handleInput(float dt,Input* in)
{
	if (CameraTrue == true)
	{
		Camera.handleInput(dt, input, width, height);
		glutWarpPointer(width / 2, height / 2);
	}
	// Handle user input
	if (in->isKeyDown('x'))
	{
		SphereBool = true;
	}
}

void Scene::update(float dt)
{
	// update scene related variables.
	Camera.update(dt);
	CameraLoad -= dt;
	if (CameraLoad <= 0)
	{
		CameraTrue = true;
	}
	if (SphereBool == true)
	{
		TimePassed -= dt;
		ButtonTime -= dt;
		if (TimePassed <= 0)
		{
			if (Seg < 20)
			{
				Seg++;
			}
			if (Size < 0.5)
			{
				Size += 0.05;
			}
			TimePassed = 1.f;
		}
		if (ButtonTime <= 0)
		{
			if (ButtonMove < 0.05)
			{
				ButtonMove += 0.005;
			}
			ButtonTime = 0.3f;
		}
		// Calculate FPS for output
		calculateFPS();
	}
}

void Scene::render() {

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	// Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt(
		Camera.GetPossition().x, Camera.GetPossition().y, Camera.GetPossition().z,
		Camera.GetLook_At().x, Camera.GetLook_At().y, Camera.GetLook_At().z,
		Camera.GetUp().x, Camera.GetUp().y, Camera.GetUp().z);
	
	// Render geometry/scene here -------------------------------------
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Grass);
	/*glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);*/

	glPushMatrix();
	Sphere.Render(Size, Seg, Seg);
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, Crate);
	glTranslatef(-2, -ButtonMove, 0);
	glRotatef(90, 1, 0, 0);
	glScalef(0.1, 0.1, 0.1);
	Cylinder.Render(1,1,6);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	



	glPushMatrix();
	glTranslatef(2, 0, 0);
	glRotatef(0, 0, 0, 0);
	Sphere.Render(0.5, 5, 5);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, -2, 0);
	for (float h = -2; h < 2; h += 0.1)
	{
		for (float i = -2; i < 2; i += 0.1)
		{
			glBegin(GL_QUADS);
			glColor3f(1, 0, 1);
				glVertex3f(i + .1, 0.0f, h + .1);
				glVertex3f(i + .1, 0.0f, h);
				glVertex3f(i, 0.0f, h);
				glVertex3f(i, 0.0f, h + .1);
				glEnd();
		}
	}
	glPopMatrix();

	//glBegin(GL_QUADS);

	//	//Front
	//	glNormal3f(0, 0, 1);

	//	glTexCoord2f(.25, .5);
	//	glVertex3f(-1, -1, 1);

	//	glTexCoord2f(.5, .5);
	//	glVertex3f(1, -1, 1);

	//	glTexCoord2f(.5, .25);
	//	glVertex3f(1, 1, 1);

	//	glTexCoord2f(.25, .25);
	//	glVertex3f(-1, 1, 1);

	//	//Left
	//	glNormal3f(-1, 0, 0);

	//	glTexCoord2f(0, .5);
	//	glVertex3f(-1, -1, -1);

	//	glTexCoord2f(.25, .5);
	//	glVertex3f(-1, -1, 1);

	//	glTexCoord2f(.25, .25);
	//	glVertex3f(-1, 1, 1);

	//	glTexCoord2f(0, .25);
	//	glVertex3f(-1, 1, -1);

	//	//Back
	//	glNormal3f(0, 0, -1);

	//	glTexCoord2f(1, .5);
	//	glVertex3f(-1, -1, -1);

	//	glTexCoord2f(.75, .5);
	//	glVertex3f(1, -1, -1);

	//	glTexCoord2f(.75, .25);
	//	glVertex3f(1, 1, -1);

	//	glTexCoord2f(1, .25);
	//	glVertex3f(-1, 1, -1);

	//	//Right
	//	glNormal3f(1, 0, 0);

	//	glTexCoord2f(.75, .5);
	//	glVertex3f(1, -1, -1);

	//	glTexCoord2f(.5, .5);
	//	glVertex3f(1, -1, 1);

	//	glTexCoord2f(.5, .25);
	//	glVertex3f(1, 1, 1);

	//	glTexCoord2f(.75, .25);
	//	glVertex3f(1, 1, -1);

	//	//Top
	//	glNormal3f(0, 1, 0);

	//	glTexCoord2f(.25, 0);
	//	glVertex3f(-1, 1, -1);

	//	glTexCoord2f(.5, 0);
	//	glVertex3f(1, 1, -1);

	//	glTexCoord2f(.5, 0.25);
	//	glVertex3f(1, 1, 1);

	//	glTexCoord2f(.25, 0.25);
	//	glVertex3f(-1, 1, 1);

	//	//Down
	//	glNormal3f(0, -1, 0);

	//	glTexCoord2f(.25, .75);
	//	glVertex3f(-1, -1, -1);

	//	glTexCoord2f(.5, .75);
	//	glVertex3f(1, -1, -1);

	//	glTexCoord2f(.5, .5);
	//	glVertex3f(1, -1, 1);

	//	glTexCoord2f(.25, .5);

	//	glVertex3f(-1, -1, 1);

	//	glEnd();

	//	glTranslatef(5, 5, 0);
	//	Disk.Render();
	//	glPopMatrix();
	//	glTranslatef(0, -5, 0);
	//	Disk.Render();
	//	glTranslatef(-5, 5, 0);
	//	Sphere.Render(2,10,10);
	//	glTranslatef(-5, 0, 0);
	//	Cylinder.Render(1, 2, 6);
	//	glTranslatef(0, -5, 0);
	//	Disk.Calculate(1, 50);
	//	Disk.Render();
	//	glTranslatef(-5, -5, 0);
glPushMatrix();
glEnable(GL_TEXTURE_2D);
glBindTexture(GL_TEXTURE_2D, Block);
glColor3f(1,1,1);
glTranslatef(0, -1, 0);
glScalef(0.005,0.005,0.005);
	My_model.render();
	glPopMatrix();
	for (int Xside = 0; Xside < 5; Xside++)
	{
		for (int Zside = 0; Zside < 5; Zside++)
		{
			glPushMatrix();
			glTranslatef(Xside * 20, 0, Zside);
			glScalef(0.005, 0.005, 0.005);
			My_model.render();
			glPopMatrix();
			
		}
	}
	// End render geometry --------------------------------------

	// Render text, should be last object rendered.
	renderTextOutput();
	
	// Swap buffers, after all objects are rendered.
	glutSwapBuffers();
}

void Scene::initialiseOpenGL()
{
	//OpenGL settings
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.39f, 0.58f, 93.0f, 1.0f);			// Cornflour Blue Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glClearStencil(0);									// Clear stencil buffer
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);
}

// Handles the resize of the window. If the window changes size the perspective matrix requires re-calculation to match new window size.
void Scene::resize(int w, int h) 
{
	width = w;
	height = h;
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	float ratio = (float)w / (float)h;
	fov = 45.0f;
	nearPlane = 0.1f;
	farPlane = 100.0f;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(fov, ratio, nearPlane, farPlane);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

// Calculates FPS
void Scene::calculateFPS()
{
	frame++;
	time = glutGet(GLUT_ELAPSED_TIME);

	if (time - timebase > 1000) {
		sprintf_s(fps, "FPS: %4.2f", frame*1000.0 / (time - timebase));
		timebase = time;
		frame = 0;
	}
}

// Compiles standard output text including FPS and current mouse position.
void Scene::renderTextOutput()
{
	// Render current mouse position and frames per second.
	sprintf_s(mouseText, "Mouse: %i, %i", input->getMouseX(), input->getMouseY());
	displayText(-1.f, 0.96f, 1.f, 0.f, 0.f, mouseText);
	displayText(-1.f, 0.90f, 1.f, 0.f, 0.f, fps);
}

// Renders text to screen. Must be called last in render function (before swap buffers)
void Scene::displayText(float x, float y, float r, float g, float b, char* string) {
	// Get Lenth of string
	int j = strlen(string);

	// Swap to 2D rendering
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, 5, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Orthographic lookAt (along the z-axis).
	gluLookAt(0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	// Set text colour and position.
	glColor3f(r, g, b);
	glRasterPos2f(x, y);
	// Render text.
	for (int i = 0; i < j; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, string[i]);
	}
	// Reset colour to white.
	glColor3f(1.f, 1.f, 1.f);

	// Swap back to 3D rendering.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov, ((float)width/(float)height), nearPlane, farPlane);
	glMatrixMode(GL_MODELVIEW);
}
