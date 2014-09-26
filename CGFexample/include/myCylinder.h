#ifndef MY_CYLINDER
#define MY_CYLINDER

#include "CGF/CGFobject.h"
#include <vector>
#include <cmath>

using namespace std;

struct Point
{
  double x, y;
};

void calculateNormal(double pt1[], double pt2[], double pt3[], double &normalX, double &normalY, double &normalZ);

class myCylinder : public CGFobject {

private:
  vector<Point> base_points;
  unsigned int nSlices, nStacks;
  bool smoothMode, textureBaseOnly;

	public:
		myCylinder(unsigned int slices, unsigned int stacks, bool smooth);
    void setTextureOnBaseOnly();
    void draw();

};



#endif
