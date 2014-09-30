#include "myDesk.h"

myChair::myChair() : angle(0), trans(0)
{}

myChair::myChair(float ang, float tran) : angle(ang), trans(tran)
{}

void myChair::draw()
{
  // aplicar a cadeira com um plástico azul elétrico
  //eletricBlue->apply();

  // rodar cadeira & move-la
  glPushMatrix();
  glTranslated(trans,0,0);
  glRotated(angle,0,1,0);

  // Desenhar as pernas da cadeira
  glPushMatrix();
  glTranslated(1 - 0.15, 1.25, 1 - 0.15);
  glScaled(0.3,2.5,0.3);
  cube.draw();
  glPopMatrix();

  glPushMatrix();
  glTranslated(- 1 + 0.15, 1.25, 1 - 0.15);
  glScaled(0.3,2.5,0.3);
  cube.draw();
  glPopMatrix();

  glPushMatrix();
  glTranslated(1 - 0.15, 1.25, - 1 + 0.15);
  glScaled(0.3,2.5,0.3);
  cube.draw();
  glPopMatrix();

  glPushMatrix();
  glTranslated(- 1 + 0.15, 1.25, - 1 + 0.15);
  glScaled(0.3,2.5,0.3);
  cube.draw();
  glPopMatrix();

  // desenhar base
  glPushMatrix();
  glTranslated(0,2.5 + 0.15,0);
  glScaled(2,0.3,2);
  cube.draw();
  glPopMatrix();

  // desenhar encosto
  glPushMatrix();
  glTranslated(0, 1.25 + 2.5 + 0.3, 1 - 0.15);
  glScaled(2, 2.5, 0.3);
  cube.draw();
  glPopMatrix();

  glPopMatrix();
}

myDesk::myDesk() : chair(), table()
{this->material_chair = NULL; }

myDesk::myDesk(CGFappearance* material_tampo, CGFappearance* material_chair) : chair(), table(material_tampo)
{
  this->material_chair = material_chair;
}

myDesk::myDesk(float ang, float tran) : chair(ang, tran), table()
{this->material_chair = NULL; }

void myDesk::draw() 
{
  // move chair and draw
  glPushMatrix();
  glTranslated(0,0,2);

  if (material_chair != NULL)
    material_chair->apply();

  chair.draw();
  glPopMatrix();

  // draw table
  table.draw();
}