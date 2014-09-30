#ifndef FLOOROBJECT_H
#define FLOOROBJECT_H

#include "CGFobject.h"
#include "CGFappearance.h"
#include "myUnitCube.h"

class myFloor: public CGFobject {
private:
  myUnitCube cube;
  unsigned int x,z;

public:
  myFloor(unsigned int xi, unsigned int zi);
  void draw();

  unsigned int getXMeasure();
  unsigned int getZMeasure();
};

#endif