#pragma once
#include "glut.h"
#include <gl/gl.h>
#include <gl/glu.h>
#include <math.h>
#include <iostream>
#include <vector>

class Sphere
{
public:
	void Render(float, int, int);
private:
	float theta;
	float delta;
	float interval;
	float P = 3.141592;
	float x, y, z;

};
