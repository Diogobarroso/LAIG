#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "Color.h"
#include "CGFlight.h"
#include <string>

class light: public CGFlight {
protected:
	bool isOmni;
	int id;
	bool enabled;
	bool marker;
	Color ambient;
	Color diffuse;
	Color specular;
	float angle;
	float exponent;
	string name;
public:
	light(unsigned int lightid, float* pos, float *dir=NULL);

	//Sets
	bool setId(int id);
	bool setName(string name);
	bool setAmbient(Color col);
	bool setDiffuse(Color col);
	bool setSpecular(Color col);
	bool setAngle(float a);
	bool setExponent(float e);
	bool setPosition(float * p);
	bool setDirection(float * d);
	bool enableMarker();
	bool disableMarker();

	//Gets
	int getId() { return id; }
	string getName() { return name; }
	bool isEnabled() { return enabled; }
	bool isMarkerEnabled() { return marker; }
	float* getPosition(){ return position; }
	float* getDirection(){ return direction; }
	float getAngle(){ return angle; }
	float getExponent(){ return exponent; }
	Color getAmbient(){ return ambient; }
	Color getDiffuse(){ return diffuse; }
	Color getSpecular(){ return specular; }

	void draw();
};

#endif
