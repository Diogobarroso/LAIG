#include "Rectangle.h"


Rectangle::Rectangle(void)
{
}

void Rectangle::draw(float s, float t)
{
	glBegin (GL_QUADS);

	glNormal3f (normalVec.getX(), normalVec.getY(), normalVec.getZ());

	for (unsigned int i = 0; i < 4; i++)
	{
		glTexCoord2f ((vertex[i].getX())/s, (vertex[i].getY())/t);
		glVertex3f ( vertex[i].getX(), vertex[i].getY(), vertex[i].getZ());
	}

	glEnd();

}

void Rectangle::calculateVertex ()
{
	addVertex(Vector3(x1,y1,0));
	addVertex(Vector3(x2,y1,0));
	addVertex(Vector3(x2,y2,0));
	addVertex(Vector3(x1,y2,0));

	normalVec = normal(vertex);
}

Rectangle::~Rectangle(void)
{
}
