#include "RotateTransformation.h"


RotateTransformation::RotateTransformation(void)
{

}

void RotateTransformation::apply ()
{
	switch (axis)
	{
	case ('x'):
		glRotatef(angle,1,0,0);
		break;
	case ('y'):
		glRotatef(angle,0,1,0);
		break;
	case ('z'):
		glRotatef(angle,0,0,1);
		break;
	default:
		break;
	}
}

bool RotateTransformation::setAxis (char axis)
{
	if (axis == 'x' || axis == 'X')
	{
		this->axis = 'x';
		return true;
	} else if ( axis == 'y' || axis == 'Y' )
	{
		this->axis = 'y';
		return true;
	} else if ( axis == 'z' || axis == 'Z' )
	{
		this->axis = 'z';
		return true;
	} else {
		printf( "\nError parsing AXIS parameter in <transform>:\nValue must be \"x\", \"y\", or \"z\";\n");
		return false;
	}
}

bool RotateTransformation::setAngle (float angle)
{
	this->angle = angle;
	return true;
}

RotateTransformation::~RotateTransformation(void)
{
}
