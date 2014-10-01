#pragma once

#include <GL/gl.h>

class Color
{
private:
	float red, green, blue, alpha;
public:
	Color();
	Color(float, float, float, float);

	float getRed() {return red;}
	float getGreen() {return green;}
	float getBlue() {return blue;}
	float getAlpha() {return alpha;}

	GLfloat * getArray();
};

