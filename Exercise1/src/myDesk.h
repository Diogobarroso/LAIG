#ifndef DESK_H
#define DESK_H

#include "CGFobject.h"
#include "myUnitCube.h"
#include "myTable.h"

class myChair: public CGFobject {
private:
  myUnitCube cube;
  CGFappearance* material;
  float angle;
  float trans;

public:
  myChair::myChair();
  myChair(float ang, float tran);
  void draw();

};

class myDesk: public CGFobject {
private:
  CGFappearance* material_chair;
  myChair chair;
  myTable table;

public:
  myDesk();
  myDesk(CGFappearance* material_tampo, CGFappearance* material_chair);
  myDesk(float ang, float tran);
  void draw();
};

#endif