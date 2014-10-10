#pragma once

#include <stdio.h>

#include "transformation.h"

class RotateTransformation :
	public Transformation
{
private:
	char axis;
	float angle;
public:
	RotateTransformation(void);

	void apply();

	bool setAxis (char axis);
	bool setAngle (float angle);

	char getAxis () { return axis; }
	float getAngle () { return angle; }

	~RotateTransformation(void);
};

