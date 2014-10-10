#pragma once

#include <string>

#include "CGFcamera.h"
#include "Vector3.h"

class Camera : public CGFcamera
{
protected:
	std::string ID;
	
	Vector3 pos;
	Vector3 target;
public:
	Camera();
	
	void setID (std::string id);

	virtual void applyView () {}

	bool setPos (float x, float y, float z);
	bool setTarget (float x, float y, float z);

	std::string getID () { return ID; }

	Vector3 getPos() { return pos; }
	Vector3 getTarget() { return target; }

	~Camera(void);
};

