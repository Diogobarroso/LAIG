#include "myUnitCube.h"

void myUnitCube::draw()
{
   double
        vertex1[3] = {0.5, 0.5, 0.5},
        vertex2[3] = {0.5, -0.5, 0.5},
        vertex3[3] = {-0.5, -0.5, 0.5},
        vertex4[3] = {-0.5, 0.5, 0.5},
        vertex5[3] = {0.5, 0.5, -0.5},
        vertex6[3] = {0.5, -0.5, -0.5},
        vertex7[3] = {-0.5, -0.5, -0.5},
        vertex8[3] = {-0.5, 0.5, -0.5};
        
    glBegin(GL_QUADS);
    
        glNormal3d(0,0,1);
        
        glTexCoord2d(1,1);
        glVertex3dv(vertex1);
        glTexCoord2d(0,1);
        glVertex3dv(vertex4);
        glTexCoord2d(0,0);
        glVertex3dv(vertex3);
        glTexCoord2d(1,0);
        glVertex3dv(vertex2);
        
    glEnd();
    
    glBegin(GL_QUADS);
    
        glNormal3d(1,0,0);
        glTexCoord2d(0,1);
        glVertex3dv(vertex1);
        glTexCoord2d(0,0);
        glVertex3dv(vertex2);
        glTexCoord2d(1,0);
        glVertex3dv(vertex6);
        glTexCoord2d(1,1);
        glVertex3dv(vertex5);

    glEnd();
    
    glBegin(GL_QUADS);
        
        glNormal3d(0,1,0);
        glTexCoord2d(0,0);
        glVertex3dv(vertex1);
        glTexCoord2d(1,0);
        glVertex3dv(vertex5);
        glTexCoord2d(1,1);
        glVertex3dv(vertex8);
        glTexCoord2d(0,1);
        glVertex3dv(vertex4);
        
    glEnd();
    
    glBegin(GL_QUADS);
    
        glNormal3d(0,0,-1);
        glTexCoord2d(0,1);
        glVertex3dv(vertex5);
        glTexCoord2d(0,0);
        glVertex3dv(vertex6);
        glTexCoord2d(1,0);
        glVertex3dv(vertex7);
        glTexCoord2d(1,1);
        glVertex3dv(vertex8);
        
    glEnd();
    
    glBegin(GL_QUADS);
    
        glNormal3d(-1,0,0);
        glTexCoord2d(1,1);
        glVertex3dv(vertex4);
        glTexCoord2d(0,1);
        glVertex3dv(vertex8);
        glTexCoord2d(0,0);
        glVertex3dv(vertex7);
        glTexCoord2d(1,0);
        glVertex3dv(vertex3);
        
    glEnd();
    
    glBegin(GL_QUADS);
    
        glNormal3d(0,-1,0);
        glTexCoord2d(1,0);
        glVertex3dv(vertex2);
        glTexCoord2d(1,1);
        glVertex3dv(vertex3);
        glTexCoord2d(0,1);
        glVertex3dv(vertex7);
        glTexCoord2d(0,0);
        glVertex3dv(vertex6);
        
    glEnd();

/*
  // XY plan
  glPushMatrix();
  glTranslated(0,0,-0.5);
  glRotated(180,0,1,0);
  glNormal3f(0,0,1);
  glRectd(-0.5,-0.5,0.5,0.5);
  glPopMatrix();

  glPushMatrix();
  glTranslated(0,0,0.5);
  glNormal3f(0,0,1);
  glRectd(-0.5,-0.5,0.5,0.5);
  glPopMatrix();

  // YZ plan
  glPushMatrix();
  glTranslated(0.5,0,0);
  glRotated(90,0,1,0); 
  glNormal3f(0,0,1);
  glRectd(-0.5,-0.5,0.5,0.5);
  glPopMatrix();

  glPushMatrix();
  glTranslated(-0.5,0,0);
  glRotated(-90,0,1,0); 
  glNormal3f(0,0,1);
  glRectd(-0.5,-0.5,0.5,0.5);
  glPopMatrix();

  //XZ plan
  glPushMatrix();
  glTranslated(0,0.5,0);
  glRotated(-90,1,0,0); 
  glNormal3f(0,0,1);
  glRectd(-0.5,-0.5,0.5,0.5);
  glPopMatrix();

  glPushMatrix();
  glTranslated(0,-0.5,0);
  glRotated(90,1,0,0);
  glNormal3f(0,0,1);
  glRectd(-0.5,-0.5,0.5,0.5);
  glPopMatrix();
  
  */
}