#pragma once
#include "primitive.h"

#include "Vector3.h"

class Triangle :
	public Primitive
{
private:
	Vector3 v1, v2, v3;
	Vector3 normalVec;
public:
	Triangle(void);

	void setV1 (Vector3 v1) {this->v1 = v1;}
	void setV2 (Vector3 v2) {this->v2 = v2;}
	void setV3 (Vector3 v3) {this->v3 = v3;}

	void draw(float, float);
	void updateNormal();

	~Triangle(void);
};

