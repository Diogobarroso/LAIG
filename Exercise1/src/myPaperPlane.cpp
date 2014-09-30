#include "myPaperPlane.h"

myPaperPlane::myPaperPlane() {
	status = 0;
	started = false;
}

void myPaperPlane::draw() {

	glPushMatrix();

	switch (status) {
	case (0):
		
		glTranslated(t/500.0,(-pow((double) ((t/500.0) - 3),2) * .1) + 1,0);
		if ((t/500.0) > 5.5) {
			started = false;
			status = 1;
			t = 0;
		}
		break;
	case (1):
		glTranslated(5.5,-t/500.0,0);
		glRotated(t/8.0,1,0,0);
		if ((t/500.0) > 1.9) {
			started = false;
			status = 2;
		}
		break;
	case (2):
		
		glTranslated(5.5,-1.9,0);
		glRotated(180,1,0,0);
		break;
	}

	glBegin(GL_TRIANGLES);

		glNormal3f(0,1,0);
		glVertex3f(1,0,0);
		glVertex3f(0,0,-0.2);
		glVertex3f(0,0,0.2);

	glEnd();

	glBegin(GL_TRIANGLES);

		glNormal3f(0,-1,0);
		glVertex3f(1,0,0);
		glVertex3f(0,0,0.2);
		glVertex3f(0,0,-0.2);

	glEnd();

	glBegin(GL_TRIANGLES);

		glNormal3f(0,0,1);
		glVertex3f(1,0,0);
		glVertex3f(0,0,0);
		glVertex3f(0,-0.1,0);

	glEnd();

	glBegin(GL_TRIANGLES);

		glNormal3f(0,0,-1);
		glVertex3f(1,0,0);
		glVertex3f(0,-0.1,0);
		glVertex3f(0,0,0);

	glEnd();

	glPopMatrix();

}


void myPaperPlane::update(unsigned long arg) {
	if (!started) {
		started = true;
		tinit = arg;
	}
	
	t = (arg - tinit);
	
}