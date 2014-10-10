
#include "light.h"

class spotLight: public light
{
private:
	float angle;
	float exponent;
	Vector3 target;
public:
	spotLight(unsigned int lightid, float* pos, float *dir=NULL);
	float getAngle();
	float getExponent();
	bool setAngle(float a);
	bool setExponent(float e);
	bool setTarget(float x, float y, float z);
	Vector3 getTarget();
};