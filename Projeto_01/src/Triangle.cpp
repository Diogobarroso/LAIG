#include "Triangle.h"


Triangle::Triangle(void)
{
}

void Triangle::draw(float s, float t)
{
	glBegin(GL_TRIANGLES);

	glNormal3f (normalVec.getX(), normalVec.getY(), normalVec.getZ());
	
	glTexCoord2f(0,0);
	glVertex3f (v1.getX(), v1.getY(), v1.getZ());
	glTexCoord2f(c/s,0);
	glVertex3f (v2.getX(), v2.getY(), v2.getZ());
	glTexCoord2f((c-a*cb)/s, (a*sb)/t);
	glVertex3f (v3.getX(), v3.getY(), v3.getZ());

	glEnd();

}

void Triangle::calculateSizes()
{
	a = sqrt(powf(v3.getX() - v2.getX(),2) +  powf(v3.getY() - v2.getY(),2) + powf(v3.getZ() - v2.getZ(),2));
	b = sqrt(powf(v1.getX() - v3.getX(),2) +  powf(v1.getY() - v3.getY(),2) + powf(v1.getZ() - v3.getZ(),2));
	c = sqrt(powf(v2.getX() - v1.getX(),2) +  powf(v2.getY() - v1.getY(),2) + powf(v2.getZ() - v1.getZ(),2));

	ca = (-powf(a,2) + powf(b,2) + powf(c,2))/(2*b*c);
	cb = (powf(a,2) - powf(b,2) + powf(c,2))/(2*a*c);
	cc = (powf(a,2) + powf(b,2) - powf(c,2))/(2*a*b);

	sb = sqrt( 1 - cb * cb);
}

void Triangle::updateNormal()
{
	std::vector<Vector3> vertexVec;
	normal(vertexVec);
}

Triangle::~Triangle(void)
{
}
