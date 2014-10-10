#pragma once

#include "GL\gl.h"
#include <vector>

#include "Vector3.h"

class Primitive
{
protected:
	std::vector<Vector3> vertex;
	void addVertex (Vector3 v) { vertex.push_back (v); }
	
	Vector3 normal (std::vector<Vector3> vertexVec);
public:
	Primitive(void);

	virtual void draw();
	
	~Primitive(void);
};

