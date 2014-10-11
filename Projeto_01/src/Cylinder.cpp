#include "Cylinder.h"


Cylinder::Cylinder(void)
{
	quadric = gluNewQuadric();
	gluQuadricTexture(quadric,true);
}

void Cylinder::draw(float, float)
{
	glPushMatrix();
	glRotated(180,1,0,0);
	gluDisk(quadric,0,base,slices,5);
	glPopMatrix();

	gluCylinder(quadric, base, top, height, slices, stacks);

	glPushMatrix();
	glTranslated(0,0,height);
	gluDisk(quadric,0,top,slices,5);
	glPopMatrix();
}

Cylinder::~Cylinder(void)
{
}
