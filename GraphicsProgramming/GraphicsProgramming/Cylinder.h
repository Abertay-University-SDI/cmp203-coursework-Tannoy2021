#pragma once
#include "glut.h"
#include <gl/gl.h>
#include <gl/glu.h>
#include <math.h>
#include <iostream>
#include <vector>
#include "Disk.h"

class Cylinder
{
public:
	Cylinder();
	void Render(float radius, float height, float segments);
private:
	Disk TopDisk;
	Disk BotDisk;
	float theta;
	float interval;
	float tau = 6.28318;
	float x, y;
	int size;
};

