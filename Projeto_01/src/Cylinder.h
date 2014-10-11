#pragma once
#include "primitive.h"
#include <GL/glu.h>

class Cylinder :
	public Primitive
{
private:

	float base, top, height;
	int slices, stacks;
	GLUquadric * quadric;

public:
	Cylinder(void);

	void setBase (float b) { base = b; }
	void setTop (float t) { top = t; }
	void setHeight (float h) { height = h; }
	void setSlices (int s) { slices = s; }
	void setStacks (int s) { stacks = s; }

	float getBase () { return base; }
	float getTop () { return top; }
	float getHeight () { return height; }
	int getSlices () { return slices; }
	int getStacks () { return stacks; }

	void draw(float, float);

	~Cylinder(void);
};

