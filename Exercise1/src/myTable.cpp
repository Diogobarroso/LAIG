#include "myTable.h"

float ambMad[3] = {0.2, 0.1, 0.05};
float difMad[3] = {0.4, 0.2, 0.1};
float specMad[3] = {0.1, 0.02, 0};
float shininessMad = 10.f;

float ambMet[3] = {0.4, 0.4, 0.4};
float difMet[3] = {0.6, 0.6, 0.6};
float specMet[3] = {0.7, 0.7, 0.7};
float shininessMet = 100.f;

myTable::myTable()
{
  madeira = new CGFappearance(ambMad,difMad,specMad,shininessMad);
  metalico = new CGFappearance(ambMet,difMet,specMet,shininessMet);
}

myTable::myTable(CGFappearance* tampo)
{
  madeira = tampo;
  metalico = new CGFappearance(ambMet,difMet,specMet,shininessMet);
}

void myTable::draw() 
{
  // Desenhar as pernas da mesa
  glPushMatrix();
  glTranslated(2.5 - 0.15, 1.75, 1.5 - 0.15);
  glScaled(0.3,3.5,0.3);
  metalico->apply();  // meter metalico nas pernas da mesa
  cube.draw();
  glPopMatrix();

  glPushMatrix();
  glTranslated(-2.5 + 0.15, 1.75, 1.5 - 0.15);
  glScaled(0.3,3.5,0.3);
  metalico->apply();  // meter metalico nas pernas da mesa
  cube.draw();
  glPopMatrix();

  glPushMatrix();
  glTranslated(2.5 - 0.15, 1.75, -1.5 + 0.15);
  glScaled(0.3,3.5,0.3);
  metalico->apply();  // meter metalico nas pernas da mesa
  cube.draw();
  glPopMatrix();

  glPushMatrix();
  glTranslated(-2.5 + 0.15, 1.75, -1.5 + 0.15);
  glScaled(0.3,3.5,0.3);
  metalico->apply();  // meter metalico nas pernas da mesa
  cube.draw();
  glPopMatrix();

  // desenhar tampo
  glPushMatrix();
  glTranslated(0, 3.5 + 0.15, 0);
  glScaled(5,0.3,3);
  madeira->apply(); // meter amadeirado no tampo
  cube.draw();
  glPopMatrix();
}