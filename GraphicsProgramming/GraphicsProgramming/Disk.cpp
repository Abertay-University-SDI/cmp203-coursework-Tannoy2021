#include "Disk.h"


extern std::vector<float> norm = { 0,0,1 };
extern std::vector<float> text = { 0.5,0.5 };
extern std::vector<float> vert = { 0,0,0 };
extern std::vector<GLubyte> indi = { 0 };

void Disk::Render()
{

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, vert.data());
	glNormalPointer(GL_FLOAT, 0, norm.data());
	glTexCoordPointer(2, GL_FLOAT, 0, text.data());

	glDrawElements(GL_TRIANGLE_FAN, size, GL_UNSIGNED_BYTE, indi.data());

	//dereferencing method of choice
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Disk::Calculate(float radius, int segment)
{
	theta = 0;
	interval = tau / segment;
	size = segment + 1;
	for (int i = 1; i < size; i++)
	{

		x = radius * cosf(theta);
		y = radius * sinf(theta);
		vert.push_back(x);
		vert.push_back(y);
		vert.push_back(0);

		norm.push_back(0);
		norm.push_back(0);
		norm.push_back(1);

		text.push_back((cosf(theta) / 2 * radius) / radius + 0.5f);
		text.push_back((sinf(theta) / 2 * radius) / radius + 0.5f);

		indi.push_back(i);
		theta += interval;
	}
	indi.push_back(1);
	size++;
}

