#include "CGFobject.h"
#include "CGFappearance.h"
#include "CGFlight.h"
#include <GL/glut.h>
#include "light.h"


class spotLight: public light
{
public:
	spotLight(unsigned int lightid, float* pos, float *dir);
	//virtual ~spotLight();

	void draw();
	void update();
	void enable();
	void disable();
	void setAmbient(float*);
	void setDiffuse(float*);
	void setSpecular(float*);
	void setKc(float f);
	void setKl(float f);
	void setKq(float f);
	void setAngle(float a);
	void setExponent(float e);
	void setPosition(float * p);
	void setTarget(float * t);
	void setName(string name);
	string getName() {return name; }

	static float background_ambient[4];

protected:
	static CGFappearance* default_light_material;

	unsigned int id;
	string name;
	float ambient[4];
	float diffuse[4];
	float specular[4];
	float exponent;
	float kc;
	float kl;
	float kq;
	float angle;
	bool enabled;

	GLUquadric* glu_quadric;

	float position[4];
	float direction[3];
	float target[3];
	CGFappearance* material;

};
