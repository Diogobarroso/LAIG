#include "myFloor.h"

myFloor::myFloor(unsigned int xi, unsigned int zi) : x(xi), z(zi)
{
}

void myFloor::draw() 
{
  glPushMatrix();
  glScaled(x,0.1,z);
  cube.draw();
  glPopMatrix();
}

unsigned int myFloor::getXMeasure()
{return x;}
unsigned int myFloor::getZMeasure()
{return z;}