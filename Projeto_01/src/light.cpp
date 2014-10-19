#include "light.h"

light::light(unsigned int lightid, float* pos, float *dir):CGFlight(lightid, pos, dir) {}

bool light::enable() {CGFlight::enable(); enabled = true; return true;}

bool light::disable() {CGFlight::disable();enabled = false; return true;}

bool light::setId(int id) {this->id = id; return true; }

bool light::setAmbient(Color col) {ambient = col; return true; }

bool light::setDiffuse(Color col) {diffuse = col; return true; }

bool light::setSpecular(Color col) {specular = col; return true; }

bool light::setPosition(float * p)
{
	p[4] = 1.0;
	pos = Vector3(p[0], p[1], p[2]);
	glLightf(GL_LIGHT0 + id, GL_POSITION, p[0]);
	return true;
}

int * light::isEnabled()
{
	int tmp;
	enabled? tmp = 1 : tmp = 0;
	return &tmp;
}

bool light::enableMarker() {marker = true; return true; }

bool light::disableMarker() {marker = false; return false; }

Color light::getAmbient() {return ambient; }

Color light::getDiffuse() {return diffuse; }

Color light::getSpecular() {return specular; }

Vector3 light::getPosition() {return pos; }

void light::draw()
{
	if(marker)
		CGFlight::draw();
	else
		CGFlight::update();
}