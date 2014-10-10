#include "Vector3.h"

Vector3::Vector3(void)
{
	x = 0;
	y = 0;
	z = 0;
}

Vector3::Vector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}


Vector3& Vector3::operator+= (const Vector3& pos2)
{
	this->x += pos2.x;
	this->y += pos2.y;
	this->z += pos2.z;

	return * this;
}

void Vector3::normalize()
{
	float length = sqrt( (x*x) + (y*y) + (z*z));

	x = x/length;
	y = y/length;
	z = z/length;
}