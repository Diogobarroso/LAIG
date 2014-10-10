#include "Triangle.h"


Triangle::Triangle(void)
{
}

void Triangle::draw()
{
	glBegin(GL_TRIANGLES);

	glNormal3f (normalVec.getX(), normalVec.getY(), normalVec.getZ());

	glVertex3f (v1.getX(), v1.getY(), v1.getZ());
	glVertex3f (v2.getX(), v2.getY(), v2.getZ());
	glVertex3f (v3.getX(), v3.getY(), v3.getZ());

	glEnd();

}

void Triangle::updateNormal()
{
	std::vector<Vector3> vertexVec;
	normal(vertexVec);
}

Triangle::~Triangle(void)
{
}
