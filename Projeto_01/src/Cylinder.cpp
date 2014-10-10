#include "Cylinder.h"


Cylinder::Cylinder(void)
{
}

void Cylinder::draw()
{
	glBegin (GL_QUADS);

	glNormal3f (normalVec.getX(), normalVec.getY(), normalVec.getZ());

	for (unsigned int i = 0; i < 4; i++)
	{
		glVertex3f ( vertex[i].getX(), vertex[i].getY(), vertex[i].getZ());
	}

	glEnd();

}

void Cylinder::calculateVertex ()
{
	addVertex(Vector3(x1,y1,0));
	addVertex(Vector3(x2,y1,0));
	addVertex(Vector3(x2,y2,0));
	addVertex(Vector3(x1,y2,0));

	normalVec = normal(vertex);
}

Cylinder::~Cylinder(void)
{
}
