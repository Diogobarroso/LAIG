#include "Sphere.h"


Sphere::Sphere(void)
{
	quadric = gluNewQuadric();
	gluQuadricTexture(quadric,true);
}

void Sphere::draw(float, float)
{
	gluSphere(quadric,radius,slices,stacks);

}

Sphere::~Sphere(void)
{
}
