#include "myClock.h"

double const pi = acos(-1.0);

// Coefficients for material for the floor
float ambDark2[3] = {0.15, 0.15, 0.15};
float difDark2[3] = {0.05, 0.05, 0.05};
float specDark2[3] = {0.1, 0.1, 0.1};
float shininessDark2 = 10.f;

// Coefficients for material for the wall
float ambLight2[3] = {0.6, 0.6, 0.6};
float difLight2[3] = {0.7, 0.7, 0.7};
float specLight2[3] = {0.6, 0.6, 0.6};
float shininessLight2 = 60.f;

myClock::myClock(bool smooth) {
  base = new myCylinder(12,1,smooth);
  base->setTextureOnBaseOnly();
  hours = new myClockHand(.4);
  minutes = new myClockHand(.6);
  seconds = new myClockHand(.7);
  hours->setAngle(0);
  minutes->setAngle(0);
  seconds->setAngle(0);

  time = 0;


  clockTexture = new CGFtexture("clock.png");

  clockAppearance = new CGFappearance(ambLight2,difLight2,specLight2,shininessLight2);
  clockAppearance->setTexture(clockTexture);

  pointerAppearance = new CGFappearance(ambDark2,difDark2,specDark2,shininessDark2);
}

void myClock::update(unsigned long arg) {
	if (time == 0)
		time = arg;

	long timediff = arg - time;
	
	seconds->setAngle( (- timediff / 1000.0) * (360/60.0) );
	minutes->setAngle( (- timediff / 1000.0) * ((360/60.0)/60.0));
	hours->setAngle( (- timediff / 1000.0) * ((360/12.0)/60.0)/60.0);
}

 void myClock::setHourAngle(float ang) {
	 hours->setAngle(ang);
 }

 void myClock::setMinuteAngle(float ang) {
	 minutes->setAngle(ang);
 }

 void myClock::setSecondAngle(float ang) {
	 seconds->setAngle(ang);
 }

myClock::~myClock() {
  delete(base);
  delete(hours);
  delete(minutes);
  delete(seconds);

  delete(clockAppearance);
  delete(clockTexture);
  delete(pointerAppearance);
}

void myClock::draw() {

  glPushMatrix();
  glScaled(1,0.1,1);
  clockAppearance->apply();
  base->draw();
  glPopMatrix();

  glPushMatrix();
  glTranslated(0,0.12,0);
  glRotated(180,0,1,0);
  glRotated(-90,1,0,0);
  pointerAppearance->apply();
  hours->draw();
  minutes->draw();
  seconds->draw();
  glPopMatrix();


}
