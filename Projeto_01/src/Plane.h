#pragma once

#include "Primitive.h"

#include <GL/glut.h>

class Plane :
	public Primitive
{
public:
	Plane(int nDivisions);
	
	void draw(float, float);

	~Plane(void);
private:
	int nDivisions;
};

