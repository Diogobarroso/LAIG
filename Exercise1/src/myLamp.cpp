#include "myLamp.h"

double const pi = acos(-1.0);

myLamp::myLamp(unsigned int slices, unsigned int stacks, bool smooth) {

  smoothMode = smooth;

  if (slices < 3) 
    nSlices = 3;
  else
    nSlices = slices;

  if (stacks < 1)
    nStacks = 1;
  else 
    nStacks = stacks;
}

void myLamp::draw()
{
  double beta = 0;
  double betaIncrement = (pi / 2) / nStacks;

  double alpha = 0;
  double alphaIncrement = 2 * pi / nSlices;

  double Sincrement = 1.0 / nSlices, Tincrement = 1.0 / nStacks;

  for (unsigned int i = 0; i < nStacks; i++) {
    alpha = 0;
    for (unsigned int j = 0; j < nSlices; j++) {
      glBegin (GL_QUADS);

      double
        vertex1[3] = {cos(beta + betaIncrement) * cos(alpha), sin(beta + betaIncrement), cos(beta + betaIncrement) * sin(alpha)},
        vertex2[3] = {cos(beta + betaIncrement) * cos(alpha + alphaIncrement), sin(beta + betaIncrement), cos(beta + betaIncrement) * sin(alpha + alphaIncrement)},
        vertex3[3] = {cos(beta) * cos(alpha + alphaIncrement), sin(beta), cos(beta) * sin(alpha + alphaIncrement)},
        vertex4[3] = {cos(beta) * cos(alpha), sin(beta), cos(beta) * sin(alpha)};

      double normalX, normalY, normalZ;

      if (!smoothMode)
        calculateNormal(vertex1, vertex2, vertex3, normalX, normalY, normalZ);

      if (smoothMode)
        glNormal3d(vertex1[0], vertex1[1], vertex1[2]);
      else
        glNormal3d(normalX, normalY, normalZ); // senão, usar a normal que calculei manualmente

      //glTexCoord2f(1,1);
      glTexCoord2f(Sincrement*j, Tincrement *(i+1));
      glVertex3dv(vertex1);

      if (smoothMode)
        glNormal3d(vertex2[0], vertex2[1], vertex2[2]);
      else
        glNormal3d(normalX, normalY, normalZ);

      //glTexCoord2f(0,1);
      glTexCoord2f(Sincrement*(j+1), Tincrement *(i+1));
      glVertex3dv(vertex2);

      if (smoothMode)
        glNormal3d(vertex3[0], vertex3[1], vertex3[2]);
      else
        glNormal3d(normalX, normalY, normalZ);

      //glTexCoord2f(0,0);
      glTexCoord2f(Sincrement*(j+1), Tincrement*i);
      glVertex3dv(vertex3);

      if (smoothMode)
        glNormal3d(vertex4[0], vertex4[1], vertex4[2]);
      else
        glNormal3d(normalX, normalY, normalZ);

      //glTexCoord2f(1,0);
      glTexCoord2f(Sincrement*j, Tincrement*i);
      glVertex3dv(vertex4);

      glEnd();

      alpha += alphaIncrement;
    }
    beta += betaIncrement;
  }
}