#pragma once
#include "Primitive.h"
#include <GL/glu.h>

class Sphere :
	public Primitive
{
private:

	float radius;
	int slices, stacks;
	GLUquadric * quadric;

public:
	Sphere(void);

	void setRadius (float r) { radius = r; }
	void setSlices (int s) { slices = s; }
	void setStacks (int s) { stacks = s; }

	void draw(float, float);

	~Sphere(void);
};

