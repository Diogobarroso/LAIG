#include "Plane.h"
#include <GL/glu.h>
#include <iostream>


Plane::Plane(void)
{
  _numDivisions = 1;
  ajusteW = 0;
  ajusteH = 0;
  texIterW = 1; // iteradores
  texIterH = 1; // iteradores
  rotate = false;
}

Plane::Plane(int n)
{
  _numDivisions = n;
  ajusteW = 0;
  ajusteH = 0;
  texIterW = 1/(double) n; // iteradores
  texIterH = 1/(double) n; // iteradores
  rotate = false;
}


Plane::~Plane(void)
{
}

void Plane::rotateTexture()
{
  rotate = true;
}

void Plane::fitTexture(int textureWidth, int textureHeight, int planeWidth, int planeHeight)
{
  double textureRatio = (double) textureWidth / textureHeight;
  double planeRatio = (double) planeWidth / planeHeight;

  double ratio = planeRatio/textureRatio;

  if (ratio > 1)
  {
    ajusteW = (ratio - 1)/2; // ajuste para cada lado tipo, 0.25 para a esquerda e 0.25 para a direita
    ajusteH = 0;

    texIterW = ratio/_numDivisions;
    texIterH = (double) 1/_numDivisions;
  }

  else
  {
    ratio = 1/ratio;
    ajusteW = 0;
    ajusteH = (ratio - 1)/2;

    texIterW = (double) 1/_numDivisions;
    texIterH = ratio/_numDivisions;
  }
}

void Plane::setTextureSize(int sizeWidth, int sizeHeight, int planeWidth, int planeHeight)
{
  if (sizeWidth > planeWidth || sizeHeight > planeHeight)
    return; // erro

  double ajusteWnovo = ((double) planeWidth/sizeWidth - 1)/2;
  double ajusteHnovo = ((double) planeHeight/sizeHeight - 1)/2;

  resizeTexture(ajusteWnovo, ajusteHnovo);
}

void Plane::resizeTexture(double ajusteWadd, double ajusteHadd)
{
  ajusteW = ajusteWadd;
  texIterW = (ajusteW*2 + 1)/_numDivisions;

  ajusteH = ajusteHadd;
  texIterH = (ajusteH*2 + 1)/_numDivisions;
}

void Plane::repeatTexture(int nRepeatS, int nRepeatT)
{
  ajusteW = nRepeatS;
  texIterW = ajusteW/_numDivisions; // put iterators as I want

  ajusteH = nRepeatT;
  texIterH = ajusteH/_numDivisions; // put iterators as I want

  ajusteW=0; // force to start in (s,t) = (0,0)
  ajusteH=0;
}

void Plane::resetTextureFit()
{
  ajusteW = 0;
  ajusteH = 0;
  texIterW = 1/(double) _numDivisions;
  texIterH = 1/(double) _numDivisions;
  rotate = false;
}

void Plane::draw()
{
  glPushMatrix();
  glRotatef(180.0,1,0,0);
  glTranslatef(-0.5,0.0,-0.5);
  glScalef(1.0/(double) _numDivisions, 1 ,1.0/(double) _numDivisions);
  glNormal3f(0,-1,0);

  if (!rotate)
  {
    for (int bx = 0; bx<_numDivisions; bx++)
    {
      glBegin(GL_TRIANGLE_STRIP);

      glTexCoord2d(-ajusteW + texIterW*bx, -ajusteH);
      glVertex3f(bx, 0, 0);


      for (int bz = 0; bz<_numDivisions; bz++)
      {
        glTexCoord2d(-ajusteW + texIterW*(bx+1), -ajusteH + texIterH*bz);
        glVertex3f(bx + 1, 0, bz);

        glTexCoord2d(-ajusteW + texIterW*bx, -ajusteH + texIterH*(bz+1));
        glVertex3f(bx, 0, bz + 1);
      }

      glTexCoord2d(-ajusteW + texIterW*(bx+1), -ajusteH + texIterH*_numDivisions);
      glVertex3d(bx+ 1, 0, _numDivisions);

      glEnd();
    }
    glPopMatrix();
  }

  else // rotate
  {
    for (int bx = 0; bx<_numDivisions; bx++)
    {
      glBegin(GL_TRIANGLE_STRIP);

      glTexCoord2d(-ajusteW, -ajusteH + texIterH*(_numDivisions - bx));
      glVertex3f(bx, 0, 0);


      for (int bz = 0; bz<_numDivisions; bz++)
      {
        glTexCoord2d(-ajusteW + texIterW*(bz), -ajusteH + texIterH*((_numDivisions) - (bx+1)));
        glVertex3f(bx + 1, 0, bz);

        glTexCoord2d(-ajusteW + texIterW*(bz + 1), -ajusteH + texIterH*((_numDivisions) - (bx)));
        glVertex3f(bx, 0, bz + 1);
      }

      glTexCoord2d(-ajusteW + texIterW*(_numDivisions), -ajusteH + texIterH*((_numDivisions) - (bx+1)));
      glVertex3d(bx+ 1, 0, _numDivisions);

      glEnd();
    }
    glPopMatrix();
  }


  /*
  glPushMatrix();
  glRotatef(180.0,1,0,0);
  glTranslatef(-0.5,0.0,-0.5);
  glScalef(1.0/(double) _numDivisions, 1 ,1.0/(double) _numDivisions); // para escalar no final
  glNormal3f(0,-1,0);

  for (int bx = 0; bx<_numDivisions; bx++)
  {
  glBegin(GL_TRIANGLE_STRIP);


  glTexCoord2d(bx/(double) _numDivisions, 0);


  glVertex3f(bx, 0, 0);


  for (int bz = 0; bz<_numDivisions; bz++)
  {
  glTexCoord2d((bx + 1)/(double) _numDivisions, bz/(double) _numDivisions);
  glVertex3f(bx + 1, 0, bz);
  glTexCoord2d(bx/(double) _numDivisions, (bz + 1)/(double) _numDivisions);
  glVertex3f(bx, 0, bz + 1);
  }
  glTexCoord2d((bx + 1)/_numDivisions,1);
  glVertex3d(bx+ 1, 0, _numDivisions);

  glEnd();
  }
  glPopMatrix();
  */
}