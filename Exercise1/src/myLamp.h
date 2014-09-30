#ifndef MY_LAMP
#define MY_LAMP

#include "CGF/CGFobject.h"
#include <vector>
#include <cmath>
#include "myCylinder.h"

using namespace std;


class myLamp : public CGFobject {

private:
  unsigned int nSlices, nStacks;
  bool smoothMode;

	public:
		myLamp(unsigned int slices, unsigned int stacks, bool smooth);

    void draw();

};



#endif
