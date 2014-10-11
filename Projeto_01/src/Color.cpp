#include "Color.h"


Color::Color()
{
	red = 0;
	green = 0;
	blue = 0;
	alpha = 1;
}

Color::Color(float r, float g, float b, float a)
{
	red = r;
	green = g;
	blue = b;
	alpha = a;
}

GLfloat* Color::getArray () {
	GLfloat *ret = (GLfloat*) malloc(4*sizeof(GLfloat));

	ret[0] = red;
	ret[1] = green;
	ret[2] = blue;
	ret[3] = alpha;

	return ret;
}