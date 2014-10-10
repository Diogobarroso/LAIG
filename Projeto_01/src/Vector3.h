#pragma once

#include <math.h>

class Vector3
{
private:
	float x, y, z;
public:
	Vector3(void);
	Vector3(float, float, float);
	float getX () { return x; }
	float getY () { return y; }
	float getZ () { return z; }
	
	void setX (float newX) { x = newX; }
	void setY (float newY) { y = newY; }
	void setZ (float newZ) { z = newZ; }

	void normalize();

	Vector3& operator+= (const Vector3& vec2);
};

