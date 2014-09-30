#include "myClockHand.h"

double const pi = acos(-1.0);

myClockHand::myClockHand()  {}

myClockHand::myClockHand(double s) {
	size = s;
	pointer = new Plane();
	angle = 0;
}

myClockHand::~myClockHand() {
  delete(pointer);
}

void myClockHand::setAngle(float ang)
{
  angle = ang;
}

void myClockHand::draw() {

  glPushMatrix();
  glRotated(angle,0,0,1);
  glTranslated(0,size/2,0);
  glScaled(1,size,1);
  glRotated(90,1,0,0);
  glScaled(0.05,1,1);
  pointer->draw();
  glPopMatrix();
}
