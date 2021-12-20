#include "Scene.h"

// Scene constructor, initilises OpenGL
// You should add further variables to need initilised.
Scene::Scene(Input *in)
{
	// Store pointer for input class
	input = in;
	initialiseOpenGL();

	// Other OpenGL / render setting should be applied here.
	My_model.load("models/breakables_ground.obj", "models/breakables_ground_c.png");
	Torch.load("models/Torch.obj", "models/Metal_A.png");

	// Colour material overrides material values so disable it
	
	glDisable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);

	Grass = SOIL_load_OGL_texture("gfx/checked.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	Skybox = SOIL_load_OGL_texture("gfx/skybox.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	Crate = SOIL_load_OGL_texture("gfx/crate.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	Block = SOIL_load_OGL_texture("models/breakables_ground_c.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	Sun = SOIL_load_OGL_texture("gfx/the-background-gff2095af4_640.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
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
	// Camera "collision" testing
	//Camera.GetPossition().x, Camera.GetPossition().y, Camera.GetPossition().z;
	//glTranslatef(-2, -ButtonMove, 3);
	// Y is 0 for the button for now 
	if (in->isKeyDown('x') 
		&& Camera.GetPossition().x > 2 && Camera.GetPossition().x < 3 
		&& Camera.GetPossition().y > -1 && Camera.GetPossition().y < 0.5
		&& Camera.GetPossition().z > 3 && Camera.GetPossition().z < 5
		&& FirstPerson == true)
	{
		SphereBool = true;
	}
	if (in->isKeyDown('o'))
	{
		EnableWireframe = true;
	}
	if (in->isKeyDown('p'))
	{
		EnableWireframe = false;
	}

	if (in->isKeyDown('m'))
	{
		SunX = 50;
		MoonX = 3.57;
		glLightfv(GL_LIGHT1, GL_POSITION, Light_Position1);
	}
	if (in->isKeyDown('n'))
	{
		SunX = 3.57;
		MoonX = 50;
		glLightfv(GL_LIGHT1, GL_POSITION, Light_Position1);
	}
	/*if (in->isKeyDown('n'))
	{
		SunX += SunX * dt;
		glLightfv(GL_LIGHT3, GL_POSITION, Light_Position3);
	}
	if (in->isKeyDown('m'))
	{
		SunX -= SunX * dt;
		glLightfv(GL_LIGHT3, GL_POSITION, Light_Position3);
	}
	if (in->isKeyDown('j'))
	{
		SunZ += SunZ * dt;
		glLightfv(GL_LIGHT3, GL_POSITION, Light_Position3);
	}
	if (in->isKeyDown('k'))
	{
		SunZ -= SunZ * dt;
		glLightfv(GL_LIGHT3, GL_POSITION, Light_Position3);
	}*/
	/*glLightfv(GL_LIGHT3, GL_POSITION, Light_Position3);*/
	// Enables first person and disables Ghost mode
	if (in->isKeyDown('f'))
	{
		FirstPerson = true;
	}

	// Disables first person and enables Ghost mode
	if (in->isKeyDown('g'))
	{
		FirstPerson = false;
	}

	//Makeshift collision 
	if (FirstPerson == true)
	{
		if (Camera.GetPossition().z < -0.36 && Camera.GetPossition().z < 1)
		{
			Camera.SetPossitionZ(-0.36);
		}
		if (Camera.GetPossition().z > 8 && Camera.GetPossition().z > 7)
		{
			Camera.SetPossitionZ(8);
		}
		/*if (Camera.GetPossition().y > 0.9 && Camera.GetPossition().y > 0.9)
		{
			Camera.SetPossitionY(-0.9);
		}*/
		//Testing restricted Y camera
		/*if (Camera.GetPossition().y < -0.9 && Camera.GetPossition().y < 1)
		{
			Camera.SetPossitionY(-0.9);
		}*/
		Camera.SetPossitionY(-0.9);
		if (Camera.GetPossition().x < -2.46 && Camera.GetPossition().x < -1)
		{
			Camera.SetPossitionX(-2.46);
		}
		if (Camera.GetPossition().x > 10 && Camera.GetPossition().x > 8)
		{
			Camera.SetPossitionX(10);
		}
		// 4 pillars
		/*glTranslatef(0.5, 0.7, 3);
		glRotatef(90, 1, 0, 0);
		glTranslatef(15, 0, 0);
		glTranslatef(0, 10, 0);
		glTranslatef(-15, 0, 0);*/
		if (Camera.GetPossition().x > -0.5 && Camera.GetPossition().x > -0.6 && Camera.GetPossition().x < 0.5 && Camera.GetPossition().z < 6.7 && Camera.GetPossition().z > 6.0)
		{
			Camera.SetPossitionX(-0.5);
		}
		if (Camera.GetPossition().x < 1.1 && Camera.GetPossition().x < 1.2 && Camera.GetPossition().x > 1 && Camera.GetPossition().z < 6.7 && Camera.GetPossition().z > 6.0)
		{
			Camera.SetPossitionX(1.1);
		}
		if (Camera.GetPossition().x > -0.5 && Camera.GetPossition().x > -0.6 && Camera.GetPossition().x < 0.5 && Camera.GetPossition().z > 5.8 && Camera.GetPossition().z > 5.7 && Camera.GetPossition().z < 6)
		{
			Camera.SetPossitionZ(5.8);
		}
		if (Camera.GetPossition().x > -0.5 && Camera.GetPossition().x > -0.6 && Camera.GetPossition().x < 0.5 && Camera.GetPossition().z < 7.2 && Camera.GetPossition().z < 7.3 && Camera.GetPossition().z > 6.5)
		{
			Camera.SetPossitionZ(7.2);
		}

		if (Camera.GetPossition().x > -0.5 && Camera.GetPossition().x > -0.6 && Camera.GetPossition().x < 0.5 && Camera.GetPossition().z < 2.2 && Camera.GetPossition().z < 2.3 && Camera.GetPossition().z > 1.1)
		{
			Camera.SetPossitionX(-0.5);
		}
		if (Camera.GetPossition().x < 1.1 && Camera.GetPossition().x < 1.2 && Camera.GetPossition().x > 1 && Camera.GetPossition().z < 2.2 && Camera.GetPossition().z < 2.3 && Camera.GetPossition().z > 1.1)
		{
			Camera.SetPossitionX(1.1);
		}
		if (Camera.GetPossition().x > -0.5 && Camera.GetPossition().x > -0.6 && Camera.GetPossition().x < 0.5 && Camera.GetPossition().z > 0.8 && Camera.GetPossition().z > 0.7 && Camera.GetPossition().z < 1)
		{
			Camera.SetPossitionZ(0.8);
		}
		if (Camera.GetPossition().x > -0.5 && Camera.GetPossition().x > -0.6 && Camera.GetPossition().x < 0.5 && Camera.GetPossition().z < 2.35 && Camera.GetPossition().z < 2.5 && Camera.GetPossition().z > 1.5)
		{
			Camera.SetPossitionZ(2.35);
		}



		if (Camera.GetPossition().x > 7 && Camera.GetPossition().x > 6.9 && Camera.GetPossition().x < 7.1 && Camera.GetPossition().z < 6.7 && Camera.GetPossition().z > 6.0)
		{
			Camera.SetPossitionX(7);
		}
		if (Camera.GetPossition().x < 8.5 && Camera.GetPossition().x < 8.6 && Camera.GetPossition().x > 7.4 && Camera.GetPossition().z < 6.7 && Camera.GetPossition().z > 6.0)
		{
			Camera.SetPossitionX(8.5);
		}
		if (Camera.GetPossition().x < 8.5 && Camera.GetPossition().x < 8.6 && Camera.GetPossition().x > 7.4 && Camera.GetPossition().z > 5.8 && Camera.GetPossition().z > 5.7 && Camera.GetPossition().z < 6)
		{
			Camera.SetPossitionZ(5.8);
		}
		if (Camera.GetPossition().x < 8.5 && Camera.GetPossition().x < 8.6 && Camera.GetPossition().x > 7.4 && Camera.GetPossition().z < 7.2 && Camera.GetPossition().z < 7.3 && Camera.GetPossition().z > 6.5)
		{
			Camera.SetPossitionZ(7.2);
		}

		if (Camera.GetPossition().x > 7 && Camera.GetPossition().x > 6.9 && Camera.GetPossition().x < 7.1 && Camera.GetPossition().z < 2.2 && Camera.GetPossition().z < 2.3 && Camera.GetPossition().z > 1.1)
		{
			Camera.SetPossitionX(7);
		}
		if (Camera.GetPossition().x < 8.5 && Camera.GetPossition().x < 8.6 && Camera.GetPossition().x > 7.4 && Camera.GetPossition().z < 2.2 && Camera.GetPossition().z < 2.3 && Camera.GetPossition().z > 1.1)
		{
			Camera.SetPossitionX(8.5);
		}
		if (Camera.GetPossition().x < 8.5 && Camera.GetPossition().x < 8.6 && Camera.GetPossition().x > 7.1 && Camera.GetPossition().z > 0.8 && Camera.GetPossition().z > 0.7 && Camera.GetPossition().z < 1)
		{
			Camera.SetPossitionZ(0.8);
		}
		if (Camera.GetPossition().x < 8.5 && Camera.GetPossition().x < 8.6 && Camera.GetPossition().x > 7.1 && Camera.GetPossition().z < 2.35 && Camera.GetPossition().z < 2.5 && Camera.GetPossition().z > 1.5)
		{
			Camera.SetPossitionZ(2.35);
		}

	}
}

void Scene::update(float dt)
{
	
	// update scene related variables.
	if (EnableWireframe == true)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else if (EnableWireframe == false)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
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
		
	}
	glLightfv(GL_LIGHT3, GL_AMBIENT, Light_Ambient3);
	glLightfv(GL_LIGHT3, GL_POSITION, Light_Position3);
	glLightf(GL_LIGHT3, GL_LINEAR_ATTENUATION, 1);
	glEnable(GL_LIGHT3);
	// Calculate FPS for output
	calculateFPS();
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
	
	//Diffuse plays the most important role in determining this colour
		//• The diffuse material will interact with the light where the object is lit
		//• Ambient materials affect the overall colour of the objectand is effected by the
		//scene ambient light




		//Sun Lights set up
		glLightfv(GL_LIGHT3, GL_AMBIENT, Light_Ambient3);
	    //glLightfv(GL_LIGHT3, GL_POSITION, Light_Position3);
		glLightf(GL_LIGHT3, GL_LINEAR_ATTENUATION, 1);
		glEnable(GL_LIGHT3);

		glLightfv(GL_LIGHT1, GL_AMBIENT, Light_Ambient1);
		//glLightfv(GL_LIGHT1, GL_POSITION, Light_Position1);
		glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 1);
		glEnable(GL_LIGHT1);


		//
		
		
		
		
		// Torch Lights
		// The spot direction is the x y z direction the light will point to
	// Y = 1 means it goes up
	// Spot_Cutoof is the cone of the light 
	// The bigger the value the more it goes to the left and the right
	// 5 would basically just be a straight line going up if Y is = 1
	// Exponent controlls how concentrated the light is at the centre
		//glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 1);
		//glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 1.0);
		//glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 1.0f);
		//
		glLightfv(GL_LIGHT0, GL_AMBIENT, Light_Ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, Light_Diffuse);
		glLightfv(GL_LIGHT0, GL_POSITION, Light_Position);
		glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0);
		glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, Spot_Direcion);
		glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 45.0f);
		glEnable(GL_LIGHT0);

		/*glLightfv(GL_LIGHT1, GL_AMBIENT, Light_Ambient1);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, Light_Diffuse1);
		glLightfv(GL_LIGHT1, GL_POSITION, Light_Position1);
		glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 1.0);
		glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, Spot_Direcion1);
		glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 25.0f);
		glEnable(GL_LIGHT1);*/
		//
		// 
		//
		glLightfv(GL_LIGHT2, GL_AMBIENT, Light_Ambient2);
		glLightfv(GL_LIGHT2, GL_DIFFUSE, Light_Diffuse2);
		glLightfv(GL_LIGHT2, GL_POSITION, Light_Position2);
		glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 1.0);
		glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, Spot_Direcion2);
		glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 30.0f);
		glEnable(GL_LIGHT2);
		//
		glLightfv(GL_LIGHT4, GL_AMBIENT, Light_Ambient4);
		glLightfv(GL_LIGHT4, GL_DIFFUSE, Light_Diffuse4);
		glLightfv(GL_LIGHT4, GL_POSITION, Light_Position4);
		glLightf(GL_LIGHT4, GL_CONSTANT_ATTENUATION, 1.0);
		glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, Spot_Direcion4);
		glLightf(GL_LIGHT4, GL_SPOT_CUTOFF, 25.0f);
		glEnable(GL_LIGHT4);


		glLightfv(GL_LIGHT5, GL_AMBIENT, Light_Ambient5);
		glLightfv(GL_LIGHT5, GL_DIFFUSE, Light_Diffuse5);
		glLightfv(GL_LIGHT5, GL_POSITION, Light_Position5);
		glLightf(GL_LIGHT5, GL_CONSTANT_ATTENUATION, 1.0);
		glLightfv(GL_LIGHT5, GL_SPOT_DIRECTION, Spot_Direcion5);
		glLightf(GL_LIGHT5, GL_SPOT_CUTOFF, 25.0f);
		glEnable(GL_LIGHT5);
		//
		//
		//
		glLightfv(GL_LIGHT6, GL_AMBIENT, Light_Ambient6);
		glLightfv(GL_LIGHT6, GL_DIFFUSE, Light_Diffuse6);
		glLightfv(GL_LIGHT6, GL_POSITION, Light_Position6);
		glLightf(GL_LIGHT6, GL_CONSTANT_ATTENUATION, 1.0);
		glLightfv(GL_LIGHT6, GL_SPOT_DIRECTION, Spot_Direcion6);
		glLightf(GL_LIGHT6, GL_SPOT_CUTOFF, 25.0f);
		glEnable(GL_LIGHT6);


		glLightfv(GL_LIGHT7, GL_AMBIENT, Light_Ambient7);
		glLightfv(GL_LIGHT7, GL_DIFFUSE, Light_Diffuse7);
		glLightfv(GL_LIGHT7, GL_POSITION, Light_Position7);
		glLightf(GL_LIGHT7, GL_CONSTANT_ATTENUATION, 1.0);
		glLightfv(GL_LIGHT7, GL_SPOT_DIRECTION, Spot_Direcion7);
		glLightf(GL_LIGHT7, GL_SPOT_CUTOFF, 25.0f);
		glEnable(GL_LIGHT7);
		//


	


	// Render geometry/scene here -------------------------------------

	//glEnable(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D, Grass);
	/*glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);*/
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glTranslatef(Camera.GetPossition().x, Camera.GetPossition().y, Camera.GetPossition().z);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Skybox);
	glColor3f(1, 1, 1);

	glBegin(GL_QUADS);

	//Front

	glNormal3f(0, 0, 1);

	glTexCoord2f(.25, .5);
	glVertex3f(-1, -1, 1);

	glTexCoord2f(.5, .5);
	glVertex3f(1, -1, 1);

	glTexCoord2f(.5, .25);
	glVertex3f(1, 1, 1);

	glTexCoord2f(.25, .25);
	glVertex3f(-1, 1, 1);

	//Left
	glNormal3f(-1, 0, 0);

	glTexCoord2f(0, .5);
	glVertex3f(-1, -1, -1);

	glTexCoord2f(.25, .5);
	glVertex3f(-1, -1, 1);

	glTexCoord2f(.25, .25);
	glVertex3f(-1, 1, 1);

	glTexCoord2f(0, .25);
	glVertex3f(-1, 1, -1);

	//Back
	glNormal3f(0, 0, -1);

	glTexCoord2f(1, .5);
	glVertex3f(-1, -1, -1);

	glTexCoord2f(.75, .5);
	glVertex3f(1, -1, -1);

	glTexCoord2f(.75, .25);
	glVertex3f(1, 1, -1);

	glTexCoord2f(1, .25);
	glVertex3f(-1, 1, -1);

	//Right
	glNormal3f(1, 0, 0);

	glTexCoord2f(.75, .5);
	glVertex3f(1, -1, -1);

	glTexCoord2f(.5, .5);
	glVertex3f(1, -1, 1);

	glTexCoord2f(.5, .25);
	glVertex3f(1, 1, 1);

	glTexCoord2f(.75, .25);
	glVertex3f(1, 1, -1);

	//Top
	glNormal3f(0, 1, 0);

	glTexCoord2f(.25, 0);
	glVertex3f(-1, 1, -1);

	glTexCoord2f(.5, 0);
	glVertex3f(1, 1, -1);

	glTexCoord2f(.5, 0.25);
	glVertex3f(1, 1, 1);

	glTexCoord2f(.25, 0.25);
	glVertex3f(-1, 1, 1);

	//Down
	glNormal3f(0, -1, 0);

	glTexCoord2f(.25, .75);
	glVertex3f(-1, -1, -1);

	glTexCoord2f(.5, .75);
	glVertex3f(1, -1, -1);

	glTexCoord2f(.5, .5);
	glVertex3f(1, -1, 1);

	glTexCoord2f(.25, .5);
	glVertex3f(-1, -1, 1);

	glEnd();
	glBindTexture(GL_TEXTURE_2D, NULL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glPopMatrix();
	glEnable(GL_LIGHTING);
	glDisable(GL_COLOR_MATERIAL);

	//Floor
	for (int Xside = 0; Xside < 7; Xside++)
	{
		glColor3f(1, 1, 1);
		for (int Zside = 0; Zside < 5; Zside++)
		{
			glPushMatrix();
			glDisable(GL_COLOR_MATERIAL);
			glTranslatef(-2 + (Xside * 2), -2.74, 0 + (Zside * 2));
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_ambient_colour);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
			glMateriali(GL_FRONT, GL_SHININESS, low_shininess);
			glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
			glRotatef(90, 1, 0, 0);
			glScalef(0.0067 * 2, 0.0067 * 2, 0.0067 * 2);
			My_model.render();
			glPopMatrix();
		}
	}
	//Roof
	for (int Xside = 1; Xside < 7; Xside++)
	{
		glColor3f(1, 1, 1);
		for (int Zside = 0; Zside < 5; Zside++)
		{
			glPushMatrix();
			glDisable(GL_COLOR_MATERIAL);
			glTranslatef(-2 + (Xside * 2), 5.2, 0 + (Zside * 2));
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_ambient_colour);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
			glMateriali(GL_FRONT, GL_SHININESS, low_shininess);
			glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
			glRotatef(180, 1, 0, 0);
			glScalef(0.0067 * 2, 0.0067 * 2, 0.0067 * 2);
			My_model.render();
			glPopMatrix();
			if (Xside == 3)
			{
				Xside = 5;
			}
		}
	}
	//Back wall
	for (int Xside = 0; Xside < 7; Xside++)
	{
		glColor3f(1, 1, 1);
		for (int Zside = 0; Zside < 3; Zside++)
		{
			glPushMatrix();
			glDisable(GL_COLOR_MATERIAL);
			glTranslatef(-2 + (Xside * 2), -0.847 + (Zside * 2), -1.55);
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_ambient_colour);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
			glMateriali(GL_FRONT, GL_SHININESS, low_shininess);
			glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
			// fixing the normals
			glRotatef(90,1,0,0);
			glScalef(0.0067 * 2, 0.0067 * 2, 0.0067 * 2);
			My_model.render();
			glPopMatrix();
		}
	}
	//Front wall
	for (int Xside = 0; Xside < 7; Xside++)
	{
		glColor3f(1, 1, 1);
		for (int Yside = 0; Yside < 3; Yside++)
		{
			glPushMatrix();
			glDisable(GL_COLOR_MATERIAL);
			glTranslatef(-2 + (Xside * 2), -0.847 + (Yside * 2), 4.72 * 2);
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_ambient_colour);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
			glMateriali(GL_FRONT, GL_SHININESS, low_shininess);
			glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
			glRotatef(180, 1, 0, 0);
			glScalef(0.0067 * 2, 0.0067 * 2, 0.0067 * 2);
			My_model.render();
			glPopMatrix();
		}
	}
	// Left wall
	for (int Zside = 0; Zside < 5; Zside++)
	{
		glColor3f(1, 1, 1);
		for (int Yside = 0; Yside < 3; Yside++)
		{
			glPushMatrix();
			glDisable(GL_COLOR_MATERIAL);
			glTranslatef(-2.87, -0.847 + (Yside * 2), 0 + (Zside * 2));
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_ambient_colour);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
			glMateriali(GL_FRONT, GL_SHININESS, low_shininess);
			glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
			glRotatef(180, 1, 0, 0);
			glScalef(0.003, 0.0067 * 2, 0.0067 * 2);
			My_model.render();
			glPopMatrix();
		}
	}
	// Right wall
	for (int Zside = 0; Zside < 5; Zside++)
	{
		glColor3f(1, 1, 1);
		for (int Yside = 0; Yside < 3; Yside++)
		{
			glPushMatrix();
			glDisable(GL_COLOR_MATERIAL);
			glTranslatef(10.87, -0.847 + (Yside * 2), 0 + (Zside * 2));
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_ambient_colour);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
			glMateriali(GL_FRONT, GL_SHININESS, low_shininess);
			glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
			glRotatef(180, 1, 0, 0);
			glScalef(0.003, 0.0067 * 2, 0.0067 * 2);
			My_model.render();
			glPopMatrix();
		}
	}

	// this creates the 4 pillars in the room
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_COLOR_MATERIAL);
	glBindTexture(GL_TEXTURE_2D, Block);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_ambient_colour);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMateriali(GL_FRONT, GL_SHININESS, low_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	glScalef(0.5, 6, 0.5);
	glTranslatef(0.5, 0.7, 3);
	glRotatef(90, 1, 0, 0);
	Cylinder.Render(1, 1, 6);
	glTranslatef(15, 0, 0);
	Cylinder.Render(1, 1, 6);
	glTranslatef(0, 10, 0);
	Cylinder.Render(1, 1, 6);
	glTranslatef(-15, 0, 0);
	Cylinder.Render(1, 1, 6);
	glPopMatrix();


	//
	// Torches on the left wall 
	glPushMatrix();
	glTranslatef(-2.65, -0.5, 4);
	glRotatef(180, 0, 1, 0);
	glScalef(0.5, 0.5, 0.5);
	Torch.render();
	glColor3f(1, 0.7, 0);
	glTranslatef(TorchX,TorchY,0);
	Sphere.Render(0.05, 20, 20);
	glPopMatrix();
	//

	// Torches on front wall 
	glPushMatrix();
	glTranslatef(3.57f, -0.5, 8.45);
	glRotatef(180, 0, 1, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(0.5, 0.5, 0.5);
	glColor3f(0, 0, 0);
	Torch.render();
	glRotatef(90, 0, -1, 0);
	glColor3f(1, 0.7, 0);
	glTranslatef(0, TorchY, -TorchZ);
	Sphere.Render(0.05, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(6.57f, -0.5, 8.45);
	glRotatef(180, 0, 1, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(0.5, 0.5, 0.5);
	glColor3f(0, 0, 0);
	Torch.render();
	glRotatef(90, 0, -1, 0);
	glColor3f(1, 0.7, 0);
	glTranslatef(0, TorchY, -TorchZ);
	Sphere.Render(0.05, 20, 20);
	glPopMatrix();
	//


	// Torches on the right wall
	glPushMatrix();
	glTranslatef(10.65, -0.5, 4);
	glRotatef(180, 0, 1, 0);
	glRotatef(180, 0, 1, 0);
	glScalef(0.5, 0.5, 0.5);
	Torch.render();
	glColor3f(1, 0.7, 0);
	glTranslatef(TorchX, TorchY, 0);
	Sphere.Render(0.05, 20, 20);
	glPopMatrix();

	//glPushMatrix();
	//glTranslatef(10.65, -0.5, 2);
	//glRotatef(180, 0, 1, 0);
	//glRotatef(180, 0, 1, 0);
	//glScalef(0.5, 0.5, 0.5);
	//Torch.render();
	//glColor3f(1, 0.7, 0);
	//glTranslatef(TorchX, TorchY, 0);
	//Sphere.Render(0.05, 20, 20);
	//glPopMatrix();
	//

	// Torches on the back wall
	glPushMatrix();
	glTranslatef(3.57f, -0.0, -0.5);
	glRotatef(180, 0, 1, 0);
	glRotatef(90, 0, -1, 0);
	glScalef(0.5, 0.5, 0.5);
	glColor3f(0, 0, 0);
	Torch.render();
	glRotatef(90, 0, -1, 0);
	glColor3f(1, 0.7, 0);
	glTranslatef(0, TorchY, -TorchZ);
	Sphere.Render(0.05, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(7.57f, -0.0, -0.5);
	glRotatef(180, 0, 1, 0);
	glRotatef(90, 0, -1, 0);
	glScalef(0.5, 0.5, 0.5);
	glColor3f(0, 0, 0);
	Torch.render();
	glRotatef(90, 0, -1, 0);
	glColor3f(1, 0.7, 0);
	glTranslatef(0, TorchY, -TorchZ);
	Sphere.Render(0.05, 20, 20);
	glPopMatrix();


	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Grass);
	glDisable(GL_COLOR_MATERIAL);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_ambient_colour);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMateriali(GL_FRONT, GL_SHININESS, low_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	glTranslatef(3.57, 0.0, 1.5);
	Sphere.Render(Size, Seg, Seg);
	
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_ambient_colour);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMateriali(GL_FRONT, GL_SHININESS, low_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	glTranslatef(4, 0, 2.5);
	Sphere.Render(Size, Seg, Seg);

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_ambient_colour);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMateriali(GL_FRONT, GL_SHININESS, low_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	glTranslatef(-4, 0, 2.5);
	Sphere.Render(Size, Seg, Seg);
	glPopMatrix();

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Sun);
	glTranslatef(SunX, 25, SunZ);
	Sphere.Render(1,20,20);
	glPopMatrix();

	/*glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, Grass);
	glDisable(GL_COLOR_MATERIAL);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_ambient_colour);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMateriali(GL_FRONT, GL_SHININESS, low_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	glTranslatef(2, 0, 2);
	Sphere.Render(Size, Seg, Seg);
	glEnable(GL_COLOR_MATERIAL);
	glPopMatrix();*/

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Crate);
	glTranslatef(3 + ButtonMove, -1, 4);
	glRotatef(90, 0, 1, 0);
	glScalef(0.1, 0.1, 0.1);
	Cylinder.Render(1,1,6);
	glPopMatrix();

	glPushMatrix();
	glDisable(GL_COLOR_MATERIAL);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_ambient_colour);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMateriali(GL_FRONT, GL_SHININESS, low_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	glTranslatef(3.57, -1.3, 4);
	glScalef(0.0067, 0.0067, 0.0067);
	glRotatef(90, 1, 0, 0);
	My_model.render();
	glPopMatrix();

	// For Color materials have disable right after the push 
	// and Enable right before the pop
	// otherwise not only the nester for loop will have the color materials but everything before it aswell !



	


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
	glClearColor(0.39f, 0.8f, 93.0f, 1.0f);			// Cornflour Blue Background
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
