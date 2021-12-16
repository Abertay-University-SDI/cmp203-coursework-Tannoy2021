#pragma once

#include "Input.h"
#include "Vector3.h"
class Camera
{
public:
	Camera();
	void update(float dt);
	void handleInput(float dt, Input* in, float Window_Width, float Window_Height);
	~Camera();
	Vector3 GetPossition();
	Vector3 SetPossitionZ(float z);
	Vector3 SetPossitionY(float y);
	Vector3 SetPossitionX(float x);
	Vector3 GetLook_At();
	Vector3 GetUp();
	float speed = 150;
	float mspeed = 5;
private:
	Vector3 Possition;
	Vector3 Look_At;
	Vector3 Up;
	Vector3 Forward;
	Vector3 Right;
	float yaw;
	float pitch;
	float roll;
};
