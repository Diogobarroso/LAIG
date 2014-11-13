#include "Patch.h"

Patch::Patch()
{
	controlPoints = std::vector<Vector3*>();
}

void Patch::draw(float s, float t)
{
	glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, order1,  0.0, 1.0, order1*3, order1,  &cntrlPoints[0]);
	glMap2f(GL_MAP2_TEXTURE_COORD_2,  0.0, 1.0, 2, order1,  0.0, 1.0, order1*2, order1,  &textpoints[0]);

	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_MAP2_NORMAL);
	glEnable(GL_MAP2_TEXTURE_COORD_2);

	glMapGrid2f(uDivisions, 0.0,1.0, vDivisions, 0.0,1.0); 

	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_TEXTURE_2D);


	glEvalMesh2(drawMode, 0,uDivisions, 0,vDivisions);

	/*
	glColor3f(1.0, 1.0, 0.0);
	for (int i = 0; i < controlPoints.size(); i++)
	{
		glRasterPos3f(cntrlPoints[i*3],cntrlPoints[i*3+1],cntrlPoints[i*3+2]);
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '0'+i);
	}
	*/
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_COLOR_MATERIAL);
}

void Patch::update()
{
	cntrlPoints = new GLfloat[controlPoints.size()*3];
	textpoints = new GLfloat[controlPoints.size()*2];

	order1 = order + 1;

	for (unsigned int i = 0; i < controlPoints.size(); i++)
	{
		Vector3 * vertex = controlPoints[i];
		cntrlPoints[i*3 + 0] = vertex->getX();
		cntrlPoints[i*3 + 1] = vertex->getY();
		cntrlPoints[i*3 + 2] = vertex->getZ();

		int u = i/(order1);
		int v = i%(order1);
		textpoints[i*2 + 0] = u/order;
		textpoints[i*2 + 1] = v/order;
	}

	switch (compute)
	{
	case(0):
		drawMode = GL_FILL;
		break;
	case (1):
		drawMode = GL_LINE;
		break;
	case (2):
		drawMode = GL_POINT;
		break;
	default:
		drawMode = GL_FILL;
		break;
	}

}

Patch::~Patch(void)
{
	delete [] cntrlPoints;
}
