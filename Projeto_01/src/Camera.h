#pragma once

#include <string>

#include "CGFcamera.h"
#include "Position.h"

class Camera : public CGFcamera
{
protected:
	std::string ID;
	
	Position pos;
	Position target;
public:
	Camera();
	
	void setID (std::string id);

	virtual void applyView () {}

	bool setPos (float x, float y, float z);
	bool setTarget (float x, float y, float z);

	std::string getID () { return ID; }

	Position getPos() { return pos; }
	Position getTarget() { return target; }

	~Camera(void);
};

