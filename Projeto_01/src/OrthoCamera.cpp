#include "OrthoCamera.h"


OrthoCamera::OrthoCamera(void)
{
}

bool OrthoCamera::setNear(float near)
{
	this->near = near;
	return true;
}

bool OrthoCamera::setFar (float far)
{
	this->far = far;
	return true;
}

bool OrthoCamera::setLeft (float left)
{
	this->left = left;
	return true;
}

bool OrthoCamera::setRight (float right)
{
	this->right = right;
	return true;
}

bool OrthoCamera::setTop (float top)
{
	this->top = top;
	return true;
}

bool OrthoCamera::setBottom (float bottom)
{
	this->bottom = bottom;
	return true;
}

bool OrthoCamera::setAxis (char axis)
{
	if (axis == 'x' || axis == 'X' || axis == 'y' || axis == 'Y' || axis == 'z' || axis == 'Z')
	{
		this->axis = axis;
		return true;
	} else {
		printf( "\nError parsing DIRECTION parameter in <cameras>:\nValue must be \"x\", \"y\", or \"z\";\n");
		return false;
	}
}

void OrthoCamera::updateProjectionMatrix(int width, int height)
{
	float aspect= (float)width / (float)height;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho (left, right, bottom, top, near, far);
	glMatrixMode(GL_MODELVIEW);
}

void OrthoCamera::applyView()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho (left, right, bottom, top, near, far);
	
	switch (axis) {
	case 'x':
		setX(10);
		setY(0);
		setZ(0);
		gluLookAt(position[0], position[1], position[2], 0,0,0, 0,0,1);
		break;
	case 'y':
		setX(0);
		setY(10);
		setZ(0);
		gluLookAt(position[0], position[1], position[2], 0,0,0, 1,0,0);
		break;
	case 'z':
		setX(0);
		setY(0);
		setZ(10);
		gluLookAt(position[0], position[1], position[2], 0,0,0, 0,1,0);
		break;
	}

	glMatrixMode(GL_MODELVIEW);	
}

OrthoCamera::~OrthoCamera(void)
{
}
