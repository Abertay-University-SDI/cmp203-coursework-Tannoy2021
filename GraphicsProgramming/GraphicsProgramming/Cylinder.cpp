#include "Cylinder.h"

Cylinder::Cylinder()
{
	BotDisk = Disk();
	TopDisk = Disk();
}


void Cylinder::Render(float radius, float height, float segments)
{

	float k = 1.0f / segments;
	BotDisk.Calculate(radius, segments);
	TopDisk.Calculate(radius, segments);
	glPushMatrix();
	BotDisk.Render();
	glBegin(GL_QUADS);
	theta = tau / segments;
	for (int i = 0; i < segments; i++)
	{
		glTexCoord2f(k * i, 0);
		glNormal3f(radius * cosf(theta * i),
			radius * sinf(theta * i),
			0);
		glVertex3f(radius * cosf(theta * i),
			radius * sinf(theta * i),
			0);

		glTexCoord2f(k * i + k, 0);
		glNormal3f(radius * cosf(theta * (i + 1)),
			radius * sinf(theta * (i + 1)),
			0);
		glVertex3f(radius * cosf(theta * (i + 1)),
			radius * sinf(theta * (i + 1)),
			0);

		glTexCoord2f(k * i + k, 1);
		glNormal3f(radius * cosf(theta * (i + 1)),
			radius * sinf(theta * (i + 1)),
			height);
		glVertex3f(radius * cosf(theta * (i + 1)),
			radius * sinf(theta * (i + 1)),
			height);

		glTexCoord2f(k * i, 1);
		glNormal3f(radius * cosf(theta * i),
			radius * sinf(theta * i),
			height);
		glVertex3f(radius * cosf(theta * i),
			radius * sinf(theta * i),
			height);
	}
	glEnd();
	glTranslatef(0, 0, height);
	TopDisk.Render();
	glPopMatrix();
}