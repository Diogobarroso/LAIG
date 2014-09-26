#include "color.h"

Color::Color() {
	red = 0;
	green = 0;
	blue = 0;
	alpha = 1;
}

Color::Color(float r, float g, float b, float a) {
	red = r;
	green = g;
	blue = b;
	alpha = a;
}

float Color::getRed() { return red;}
float Color::getGreen() {return green;}
float Color::getBlue() {return blue;}
float Color::getAlpha() {return alpha;}