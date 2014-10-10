#include "spotLight.h"

float spotLight::getAngle() { return angle;}
float spotLight::getExponent() {return exponent; }

bool spotLight::setAngle(float a) {angle = a; return true; }
bool spotLight::setExponent(float e) {exponent = e; return true; }
bool spotLight::setTarget(float x, float y, float z) {target = Vector3(x,y,z); return true;}

spotLight::spotLight(unsigned int lightid, float* pos, float *dir):light(lightid, pos, dir) {}