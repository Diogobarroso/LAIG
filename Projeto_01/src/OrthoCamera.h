#pragma once

#include "camera.h"
#include "GL\gl.h"
#include "GL\glu.h"

class OrthoCamera : public Camera
{
//	 <ortho id="ss" direction="ee" near="ff" far="ff" left="ff" right="ff" top="ff" bottom="ff" />
private:

	float near;
	float far;

	float left;
	float right;

	float top;
	float bottom;

	char axis;

public:
	OrthoCamera(void);

	void updateProjectionMatrix(int width, int height);
	void applyView();

	bool setNear (float near);
	bool setFar (float far);

	bool setLeft (float left);
	bool setRight (float right);
	
	bool setTop (float top);
	bool setBottom (float bottom);

	bool setAxis (char axis);


	float getNear () { return near; }
	float getFar () { return far; }

	float getLeft () { return left; }
	float getRight () { return right; }

	float getTop () { return top; }
	float getBottom () { return bottom; }

	char getAxis () { return axis; }

	~OrthoCamera(void);
};

