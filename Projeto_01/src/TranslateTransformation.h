#pragma once
#include "Transformation.h"
class TranslateTransformation :
	public Transformation
{
private:
	float x,y,z;
public:
	TranslateTransformation(void);
	TranslateTransformation(float x, float y, float z) : x(x), y(y), z(z) {};

	void apply();

	~TranslateTransformation(void);
};

