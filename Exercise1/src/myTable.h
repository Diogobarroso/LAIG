#ifndef TABLEOBJECT_H
#define TABLEOBJECT_H

#include "CGFobject.h"
#include "CGFappearance.h"
#include "myUnitCube.h"

class myTable: public CGFobject {
private:
  myUnitCube cube;
  CGFappearance* madeira;
  CGFappearance* metalico;
  float angle;

public:
  myTable();
  myTable(CGFappearance* tampo);
  void draw();
};

#endif