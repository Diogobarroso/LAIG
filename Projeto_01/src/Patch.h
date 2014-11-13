#pragma once

#include "Primitive.h"

#include <GL/glut.h>

class Patch :
	public Primitive
{
public:
	Patch();
	
	void draw(float, float);

	void update();

	void setOrder (int o) { order = o; }
	void setUDivisions (int u) { uDivisions = u; }
	void setVDivisions (int v) { vDivisions = v; }
	void setCompute (int c) { compute = c; }
	void addPoint (Vector3* p) { controlPoints.push_back(p); }

	int getOrder () { return order; }

	int nPoints () { return controlPoints.size(); }

	~Patch(void);
private:
	
	int order;
	int order1;
	int uDivisions;
	int vDivisions;
	int compute;

	GLenum drawMode;

	std::vector<Vector3*> controlPoints;

	GLfloat* cntrlPoints;
	GLfloat* textpoints;
};

