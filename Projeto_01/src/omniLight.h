
#include "light.h"

class omniLight: public light
{
	string name;
public:
	omniLight(unsigned int lightid, float* pos, float *dir=NULL);
	Vector3 * getTarget() {return NULL;}
	float * getExponent() {return NULL;}
	void setName(string name);
	string getName() {return name; }
};