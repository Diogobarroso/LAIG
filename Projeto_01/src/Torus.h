#pragma once
#include "Primitive.h"
#include <vector>

class Torus :
	public Primitive
{
private:

	float innerRadius, outerRadius;
	int slices, loops;

	std::vector< std::vector< Vector3> > vertices;

public:
	Torus(void);

	void setInner (float i) { innerRadius = i; }
	void setOuter (float o) { outerRadius = o; }
	void setSlices (int s) { slices = s; }
	void setLoops (int l) { loops = l; }

	void generateVertices();

	void draw(float, float);

	~Torus(void);
};

