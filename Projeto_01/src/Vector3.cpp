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


Vector3 Vector3::operator+ (const Vector3& v2)
{
	Vector3 result;

	result.x = this->x + v2.x;
	result.y = this->y + v2.y;
	result.z = this->z + v2.z;

	return result;
}

Vector3 Vector3::operator- (const Vector3& v2)
{
	Vector3 result;

	result.x = this->x - v2.x;
	result.y = this->y - v2.y;
	result.z = this->z - v2.z;

	return result;
}

Vector3 Vector3::operator* (float s)
{
	Vector3 result;

	result.x = this->x * s;
	result.y = this->y * s;
	result.z = this->z * s;

	return result;
}

void Vector3::normalize()
{
	float length = sqrt( (x*x) + (y*y) + (z*z));

	x = x/length;
	y = y/length;
	z = z/length;
}