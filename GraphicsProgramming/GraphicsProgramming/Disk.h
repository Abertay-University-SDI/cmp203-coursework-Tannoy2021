#pragma once
#include "glut.h"
#include <gl/gl.h>
#include <gl/glu.h>
#include <math.h>
#include <iostream>
#include <vector>

class Disk
{
public:
	void Render();
	void Calculate(float, int);
private:
	float theta;
	float interval;
	float tau = 6.28318;
	float x, y;
	int size;



};

