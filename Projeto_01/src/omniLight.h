
#include "light.h"

class omniLight: public light
{
public:
	omniLight(unsigned int lightid, float* pos, float *dir=NULL);
	Vector3 * getTarget() {return NULL;}
	float * getExponent() {return NULL;}
};