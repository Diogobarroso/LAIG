#ifndef MY_CLOCK_HAND
#define MY_CLOCK_HAND

#include "CGF/CGFobject.h"
#include "Plane.h"
#include <vector>
#include <cmath>

using namespace std;

class myClockHand : public CGFobject {

private:
  Plane* pointer;
  float angle;
  double size;

	public:
		myClockHand();
		myClockHand(double size);
		~myClockHand();
		void setAngle(float ang);
		float getAngle() {return angle;}
    void draw();
};



#endif
