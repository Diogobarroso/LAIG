#pragma once

#include <string>

#include "Camera.h"
#include "CGFcamera.h"
#include "GL\gl.h"
#include "GL\glu.h"
#include "Position.h"

class PerspectiveCamera: public Camera
{
private:

	float near;
	float far;
	float angle;


public:

	PerspectiveCamera(void);

	bool setNear (float near);
	bool setFar (float far);
	bool setAngle (float angle);

	float getNear() { return near; }
	float getFar() { return far; }
	float getAngle() { return angle; }

	void updateProjectionMatrix(int width, int height);
	void applyView();

	~PerspectiveCamera(void);


};

