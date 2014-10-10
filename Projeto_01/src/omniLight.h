
#include "light.h"

class omniLight: public light
{
public:
	omniLight(unsigned int lightid, float* pos, float *dir=NULL);
};