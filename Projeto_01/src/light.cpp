#include "light.h"

light::light(unsigned int lightid, float* pos, float *dir):CGFlight(lightid, pos, dir) {
	if( dir == NULL )
		isOmni = true;
	else
		isOmni = false;
}

bool light::setId(int id) {this->id = id; return true; }
bool light::setName(string name) {this->name = name; return true; }
/*
bool light::setAmbient(Color col) {ambient.setAmbient( col.getArray()); return true; }
bool light::setDiffuse(Color col) {diffuse = col.getArray(); return true; }
bool light::setSpecular(Color col) {specular = col.getArray(); return true; }
*/
bool light::setAngle(float a)
{
	angle = a;
	glLightf( GL_LIGHT0+id, GL_SPOT_CUTOFF, angle );
	return true;
}
bool light::setExponent(float e)
{
	exponent = e;
	glLightf( GL_LIGHT0+id, GL_SPOT_EXPONENT, exponent );
	return true;
}

bool light::setPosition(float * p)
{
	for( int i=0; i<4; i++ )
		position[i] = p[i];
	return true;
}
bool light::setDirection(float * p)
{
	for( int i=0; i<3; i++ )
		direction[i] = p[i];
	return true;
}

bool light::enableMarker() {marker = true; return true; }

bool light::disableMarker() {marker = false; return false; } //Return false?

void light::draw()
{
	if( marker )
		CGFlight::draw();
	else
		CGFlight::update();
}
