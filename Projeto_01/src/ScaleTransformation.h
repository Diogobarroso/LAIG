#pragma once
#include "Transformation.h"
class ScaleTransformation :
	public Transformation
{
private:
	float x,y,z;
public:
	ScaleTransformation(void);
	ScaleTransformation(float x, float y, float z) : x(x), y(y), z(z) {};

	void apply();



	~ScaleTransformation(void);
};

