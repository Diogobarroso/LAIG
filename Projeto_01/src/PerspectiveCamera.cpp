#include "PerspectiveCamera.h"

PerspectiveCamera::PerspectiveCamera(void)
{

}

bool PerspectiveCamera::setNear (float near)
{
	this->near = near;
	return true;
}

bool PerspectiveCamera::setFar (float far)
{
	this->far = far;
	return true;
}

bool PerspectiveCamera::setAngle (float angle)
{
	this->angle = angle;
	return true;
}


void PerspectiveCamera::updateProjectionMatrix(int width, int height)
{
	float aspect= (float)width / (float)height;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(angle, aspect, near, far);
}

void PerspectiveCamera::applyView()
{
	gluLookAt(pos.getX(), pos.getY(), pos.getZ(), target.getX(), target.getY(),target.getZ(), 0.0, 1.0, 0.0);
}

PerspectiveCamera::~PerspectiveCamera(void)
{
}
