#include "Camera.h"

Camera::Camera()
{
	Possition = Vector3(-0.7, -0.5, 8);
	Look_At = Vector3(0, 0, 0);
	Up = Vector3(0, 1, 0);
	Forward = Vector3(0, 0, 0);
	Right = Vector3(0, 0, 0);
	yaw = 0;
	pitch = 0;
	roll = 0;
}

void Camera::handleInput(float dt, Input* in, float Window_Width, float Window_Height)
{
	float X_Center;
	float Y_Center;

	X_Center = Window_Width / 2;
	Y_Center = Window_Height / 2;


	if (in->getMouseX() - X_Center > 1)
	{
		yaw += speed * dt;
	}
	else if (in->getMouseX() - X_Center < -1)
	{
		yaw -= speed * dt;
	}
	if (in->getMouseY() - Y_Center > 1)
	{

		pitch -= speed * dt;
	}
	if (in->getMouseY() - Y_Center < -1)
	{
		pitch += speed * dt;
	}

	if (in->isKeyDown('w'))
	{
		Possition.add(Forward, mspeed * dt);
	}
	else if (in->isKeyDown('s'))
	{
		Possition.add(Forward, -mspeed * dt);
	}
	if (in->isKeyDown('a'))
	{
		Possition.add(Right, -mspeed * dt);
	}
	else if (in->isKeyDown('d'))
	{
		Possition.add(Right, mspeed * dt);
	}
	if (in->isKeyDown('q'))
	{
		Possition.add(Up, -mspeed * dt);
	}
	else if (in->isKeyDown('e'))
	{
		Possition.add(Up, mspeed * dt);
	}
}

void Camera::update(float dt)
{
	float cosR, cosP, cosY;
	float sinR, sinP, sinY;

	cosY = cosf(yaw * 3.1415 / 180);
	cosP = cosf(pitch * 3.1415 / 180);
	cosR = cosf(roll * 3.1415 / 180);
	sinY = sinf(yaw * 3.1415 / 180);
	sinP = sinf(pitch * 3.1415 / 180);
	sinR = sinf(roll * 3.1415 / 180);

	/*Look_At.x = sinY * cosP;
	Look_At.y = sinP;
	Look_At.z = cosP * -cosY;*/

	Up.x = -cosY * sinR - sinY * sinP * cosR;
	Up.y = cosP * cosR;
	Up.z = -sinY * sinR - sinP * cosR * -cosY;

	Look_At = Possition + Forward;

	Forward.x = sinY * cosP;
	Forward.y = sinP;
	Forward.z = cosP * -cosY;

	Right = Forward.cross(Up);
}

Vector3 Camera::GetLook_At()
{
	return Look_At;
}

Vector3 Camera::GetPossition()
{
	return Possition;
}

Vector3 Camera::SetPossitionZ(float z)
{
	Possition = Vector3(GetPossition().x,GetPossition().y,z);
	return Possition;
}

Vector3 Camera::SetPossitionY(float y)
{
	Possition = Vector3(GetPossition().x, y, GetPossition().z);
	return Possition;
}

Vector3 Camera::SetPossitionX(float x)
{
	Possition = Vector3(x,GetPossition().y, GetPossition().z);
	return Possition;
}

Vector3 Camera::GetUp()
{
	return Up;
}

Camera::~Camera()
{

}