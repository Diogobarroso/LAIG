#include "Camera.h"


Camera::Camera(void)
{
}


void Camera::setID (std::string id)
{
	ID = id;
}

bool Camera::setPos (float x, float y, float z)
{
	pos = Vector3(x,y,z);
	return true;
}

bool Camera::setTarget (float x, float y, float z)
{
	target = Vector3 (x,y,z);
	return true;
}


Camera::~Camera(void)
{
}
