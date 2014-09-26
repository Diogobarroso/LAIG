#pragma once

#include "CGF/CGFobject.h"
class Plane
{
public:
	Plane(void);
	Plane(int);
	~Plane(void);
  void fitTexture(int textureWidth, int textureHeight, int planeWidth, int planeHeight); /* double textureRatio, double planeRatio */
  void resizeTexture(double ajusteWadd, double ajusteHadd);
  void setTextureSize(int sizeWidth, int sizeHeight, int planeWidth, int planeHeight);
  void repeatTexture(int nRepeatS, int nRepeatT);
  void resetTextureFit();
  void rotateTexture();
	void draw();
private:
	int _numDivisions; // Number of triangles that constitute rows/columns
  double ajusteW, ajusteH, texIterW, texIterH;
  bool rotate;
};

