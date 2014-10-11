#pragma once
#include "primitive.h"
class Rectangle :
	public Primitive
{
private:
	float x1, x2, y1, y2;
	Vector3 translateToOrigin;
	Vector3 normalVec;
	
public:
	Rectangle(void);

	void setX1 (float x1) { this->x1 = x1; }
	void setX2 (float x2) { this->x2 = x2; }
	void setY1 (float y1) { this->y1 = y1; }
	void setY2 (float y2) { this->y2 = y2; }

	void draw(float, float);
	void calculateVertex ();

	~Rectangle(void);
};

