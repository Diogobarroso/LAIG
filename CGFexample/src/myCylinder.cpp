#include "myCylinder.h"

double const pi = acos(-1.0);

void calculateNormal(double pt1[], double pt2[], double pt3[], double &normalX, double &normalY, double &normalZ)
{
  /*
  double vec2[3] = {pt3[0] - pt1[0], pt3[1] - pt1[1], pt3[2] - pt2[2]};
  double vec1[3] = {pt2[0] - pt1[0], pt2[1] - pt1[1], pt2[2] - pt2[2]};

  normalX = vec1[1]*vec2[2] - vec2[1]*vec1[2];
  normalY = vec2[0]*vec1[2] - vec1[0]*vec2[2];
  normalZ = vec1[0]*vec2[1] - vec2[0]*vec1[1];
  */

  double Qx, Qy, Qz, Px, Py, Pz;

  Px = pt2[0]-pt1[0];
  Py = pt2[1]-pt1[1];
  Pz = pt2[2]-pt1[2];
  Qx = pt3[0]-pt1[0];
  Qy = pt3[1]-pt1[1];
  Qz = pt3[2]-pt1[2];

  normalX = Py*Qz - Pz*Qy;
  normalY = Pz*Qx - Px*Qz;
  normalZ = Px*Qy - Py*Qx;

  double vectorNorma = sqrt(pow(normalX,2) + pow(normalY,2) + pow(normalZ,2));

  normalX /= vectorNorma;
  normalY /= vectorNorma;
  normalZ /= vectorNorma;
}

myCylinder::myCylinder(unsigned int slices, unsigned int stacks, bool smooth) {

  smoothMode = smooth;
  textureBaseOnly = false;

  if (slices < 3) 
    nSlices = 3;
  else
    nSlices = slices;

  if (stacks < 1)
    nStacks = 1;
  else 
    nStacks = stacks;

  double ang=0, angIncrement = 2 * pi / nSlices;

  for(unsigned int i=0; i < nSlices; i++)
  {
    Point ponto;
    ponto.x = cos(ang);
    ponto.y = sin(ang);

    base_points.push_back(ponto);

    ang += angIncrement;
  }
}

void myCylinder::setTextureOnBaseOnly()
{
  textureBaseOnly = true;
}

void myCylinder::draw()
{
  glBegin(GL_POLYGON);

  glNormal3d(0,-1,0);

  for(unsigned int i=0; i < base_points.size(); i++) {
    if (!textureBaseOnly)
      glTexCoord2f(1- (base_points[i].x/2 + 0.5), base_points[i].y/2 + 0.5);

    glVertex3d(base_points[i].x, 0, base_points[i].y);
  }

  glEnd();

  double zIncrement = 1.0 / nStacks;
  double z = 0;

  double Sincrement = 1.0 / nSlices, Tincrement = 1.0 / nStacks;

  for (unsigned int i = 0; i < nStacks; i++) {
    for (unsigned int j = 0; j < nSlices; j++) {

      glBegin(GL_QUADS);

      double
        vertex1[3] = {base_points[j].x, z + zIncrement, base_points[j].y},
        vertex2[3] = {base_points[(j+1)%nSlices].x, z + zIncrement, base_points[(j+1)%nSlices].y},
        vertex3[3] = {base_points[(j+1)%nSlices].x, z, base_points[(j+1)%nSlices].y},
        vertex4[3] = {base_points[j].x, z, base_points[j].y};

      double normalX, normalY, normalZ;

      if (!smoothMode)
        calculateNormal(vertex1, vertex2, vertex3, normalX, normalY, normalZ);

      if (smoothMode) // se está em smooth mode, a normal é igual às coordenadas.
        glNormal3d(vertex1[0], vertex1[1], vertex1[2]);
      else
        glNormal3d(normalX, normalY, normalZ); // senão, usar a normal que calculei manualmente
    
      if (!textureBaseOnly)
        glTexCoord2f(Sincrement*j, Tincrement *(i+1));

      glVertex3dv(vertex1);

      if (smoothMode)
        glNormal3d(vertex2[0], vertex2[1], vertex2[2]);
      else
        glNormal3d(normalX, normalY, normalZ);

      if (!textureBaseOnly)
        glTexCoord2f(Sincrement*(j+1), Tincrement *(i+1));

      glVertex3dv(vertex2);

      if (smoothMode)
        glNormal3d(vertex3[0], vertex3[1], vertex3[2]);
      else
        glNormal3d(normalX, normalY, normalZ);

      if (!textureBaseOnly)
        glTexCoord2f(Sincrement*(j+1), Tincrement*i);

      glVertex3dv(vertex3);

      if (smoothMode)
        glNormal3d(vertex4[0], vertex4[1], vertex4[2]);
      else
        glNormal3d(normalX, normalY, normalZ);

      if (!textureBaseOnly)
        glTexCoord2f(Sincrement*j, Tincrement*i);

      glVertex3dv(vertex4);

      glEnd();
    }
    z += zIncrement;
  }

  glBegin(GL_POLYGON);

  glNormal3d(0,1,0);

  for(int i=base_points.size() - 1; i >= 0; i--) {
    glTexCoord2f(1- (base_points[i].x/2 + 0.5), base_points[i].y/2 + 0.5);
    glVertex3d(base_points[i].x, 1, base_points[i].y);
  }

  glEnd();
}