#ifndef LightingScene_H
#define LightingScene_H

#include "CGFscene.h"
#include "CGFappearance.h"
#include "myDesk.h"
#include "myTable.h"
#include "Plane.h"
#include "myCylinder.h"
#include "myLamp.h"
#include "myClock.h"
#include "myClockHand.h"
#include "myPaperPlane.h"

class LightingScene : public CGFscene
{
public:
  void init();
  void display();

  void update(unsigned long arg);

  CGFlight* light0;
  CGFlight* light1;
  CGFlight* light2;
  CGFlight* light3;
  CGFlight* light4;
  CGFlight* light5;

  CGFobject* cilindro1;
  CGFobject* cilindro2;

  CGFobject* lamp1;
  CGFobject* lamp2;
  CGFobject* lamp3;

  myClock* clock;
  CGFobject* hourPointer;
  
  myPaperPlane* airPlane;

  CGFobject* table;
  Plane* wall;
  Plane* boardA;
  Plane* boardB;
  CGFappearance* materialA;
  CGFappearance* materialB;
  CGFappearance* dark;
  CGFappearance* light;
  CGFappearance* eletricBlue;

  CGFtexture* tableTexture;
  CGFtexture* slideTexture;
  CGFtexture* boardTexture;
  CGFtexture* windowTexture;
  CGFtexture* floorTexture;
  CGFtexture* wallTexture;
  CGFtexture* marmoreTexture;

  CGFappearance* tableAppearance;
  CGFappearance* slidesAppearance;
  CGFappearance* boardAppearance;
  CGFappearance* windowAppearance;
  CGFappearance* floorAppearance;
  CGFappearance* wallAppearance;
  CGFappearance* marmoreAppearance;

  ~LightingScene();
};

#endif