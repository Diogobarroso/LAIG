#ifndef MY_CLOCK
#define MY_CLOCK

#include "CGF/CGFobject.h"
#include "myClockHand.h"
#include "myCylinder.h"
#include "CGFappearance.h"
#include <vector>
#include <cmath>

using namespace std;

class myClock : public CGFobject {

private:
  myCylinder* base;
  myClockHand *hours, *minutes, *seconds;

  CGFtexture* clockTexture;
  CGFappearance* clockAppearance;
  CGFappearance* pointerAppearance;

  unsigned long time;


public:
  myClock(bool smooth);
  void setHourAngle(float ang);
  void setMinuteAngle(float ang);
  void setSecondAngle(float ang);
  void update(unsigned long arg);
  ~myClock();
  void draw();

};



#endif
