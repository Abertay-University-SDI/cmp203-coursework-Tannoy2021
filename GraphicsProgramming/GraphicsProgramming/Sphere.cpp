#include "Sphere.h"

void Sphere::Render(float radius, int Long, int Lat)
{
	theta = (2 * P) / Lat;
	delta = P / Long;

	float LatSet = 1.0f / Lat;
	float LongSet = 1.0f / Long;
	glBegin(GL_QUADS);
	for (int i = 0; i < Lat; i++)
	{
		for (int j = 0; j < Long; j++)
		{
			glTexCoord2f(j * LongSet, i * LatSet);
			glNormal3f(radius * cos(theta * j) * sin(delta * i),
				radius * cos(delta * i),
				radius * sin(theta * j) * sin(delta * i));
			glVertex3f(radius * cos(theta * j) * sin(delta * i),
				radius * cos(delta * i),
				radius * sin(theta * j) * sin(delta * i));

			glTexCoord2f(j * LongSet + LongSet, i * LatSet);
			glNormal3f(radius * cos(theta * (j + 1)) * sin(delta * i),
				radius * cos(delta * i),
				radius * sin(theta * (j + 1)) * sin(delta * i));
			glVertex3f(radius * cos(theta * (j + 1)) * sin(delta * i),
				radius * cos(delta * i),
				radius * sin(theta * (j + 1)) * sin(delta * i));

			glTexCoord2f(j * LongSet + LongSet, i * LatSet + LatSet);
			glNormal3f(radius * cos(theta * (j + 1)) * sin(delta * (i + 1)),
				radius * cos(delta * (i + 1)),
				radius * sin(theta * (j + 1)) * sin(delta * (i + 1)));
			glVertex3f(radius * cos(theta * (j + 1)) * sin(delta * (i + 1)),
				radius * cos(delta * (i + 1)),
				radius * sin(theta * (j + 1)) * sin(delta * (i + 1)));

			glTexCoord2f(j * LongSet, i * LatSet + LatSet);
			glNormal3f(radius * cos(theta * j) * sin(delta * (i + 1)),
				radius * cos(delta * (i + 1)),
				radius * sin(theta * j) * sin(delta * (i + 1)));
			glVertex3f(radius * cos(theta * j) * sin(delta * (i + 1)),
				radius * cos(delta * (i + 1)),
				radius * sin(theta * j) * sin(delta * (i + 1)));
		}
	}

	glEnd();
}