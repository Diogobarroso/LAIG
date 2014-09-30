#ifndef MYPLANE_H
#define MYPLANE_H

#include "CGFobject.h"
#include <iostream>

using namespace std;

class myPaperPlane: public CGFobject {
	public:
		myPaperPlane();
		void draw();
		void update(unsigned long arg);
private:
	int status, t, tinit;
	bool started;
};

#endif