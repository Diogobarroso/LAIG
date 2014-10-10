#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "Color.h"
#include "CGFlight.h"
#include "Vector3.h"

class light: public CGFlight {
protected:
	std::string id;
	bool enabled;
	bool marker;
	Color ambient;
	Color diffuse;
	Color specular;
	Vector3 pos;
public:
	light(unsigned int lightid, float* pos, float *dir=NULL);
	std::string getId();
	bool enable();
	bool disable();
	bool setId(std::string id);
	bool setAmbient(Color col);
	bool setDiffuse(Color col);
	bool setSpecular(Color col);
	bool setPosition(float a, float b, float c);
	bool isEnabled();
	bool isMarkerEnabled() {return marker; }
	bool enableMarker();
	bool disableMarker();
	Color getAmbient();
	Color getDiffuse();
	Color getSpecular();
	Vector3 getPosition();

	void draw();
};

#endif