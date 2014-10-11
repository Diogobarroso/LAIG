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
		glTexCoord2f ((vertex[i].getX() - translateToOrigin.getX())/s, (vertex[i].getY() - translateToOrigin.getY())/t);
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
	
	translateToOrigin = Vector3();
	if (x1 > x2)
		translateToOrigin.setX(x2);
	else
		translateToOrigin.setX(x1);

	if (y1 > y2)
		translateToOrigin.setY(y2);
	else
		translateToOrigin.setY(y1);
}

Rectangle::~Rectangle(void)
{
}
