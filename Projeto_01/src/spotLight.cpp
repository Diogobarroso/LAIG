#include "CGFlight.h"

#include "CGFapplication.h"

#include "spotLight.h"

spotLight::spotLight(unsigned int lightid, float* pos, float *dir):light(lightid, pos, dir)
{
	id = lightid;
	for(int i = 0; i < 4; i++)
	{
		position[i] = pos[i];
		direction[i] = dir[i];
	}
	//CGFlight::CGFlight(lightid, pos, dir);
}

void spotLight::setAmbient(float* li) {
	for(int i = 0; i < 4; i++)
		ambient[i] = li[i];
	CGFlight::setAmbient(li);
}

void spotLight::setDiffuse(float* li) {
	for(int i = 0; i < 4; i++)
		diffuse [i] = li[i];
	CGFlight::setDiffuse(li);
}

void spotLight::setSpecular(float* li) {
	for(int i = 0; i < 4; i++)
		specular[i] = li[i];
	CGFlight::setSpecular(li);
}

void spotLight::enable() {
	enabled=true;
	CGFlight::enable();
}

void spotLight::disable() {
	enabled=false;
	CGFlight::disable();
}

void spotLight::update() {
	CGFlight::update();
}

void spotLight::draw() {
	if(enabled)
		CGFlight::draw();
	else
		CGFlight::update();
}

void spotLight::setKc(float f) { CGFlight::setKc(f); }
void spotLight::setKl(float f) { CGFlight::setKc(f); }
void spotLight::setKq(float f) { CGFlight::setKc(f); }

void spotLight::setAngle(float a) { CGFlight::setAngle(a); }


void spotLight::setExponent(float e) { exponent = e; glLightf(id, GL_SPOT_EXPONENT, exponent); }

void spotLight::setPosition(float * p)
{
	for(int i = 0; i < 3; i++)
	{
		position[i] = p[i];
		direction[i] = target[i] - position[i];
	}
	light::setPosition(p);
}

void spotLight::setTarget(float * t)
{
	for(int i = 0; i < 3; i++)
	{
		target[i] = t[i];
		direction[i] = target[i] - position[i];
	}
}

void spotLight::setName(string n)
{
	name = n;
}