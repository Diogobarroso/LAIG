#pragma once

#include "Plane.h"
#include "CGFshader.h"
#include "CGFtexture.h"
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glut.h>

class Flag: public Plane
{
protected:
	CGFtexture * baseTexture;
	CGFtexture * heightTexture;

	GLint baseImageLoc;
	GLint heightImageLoc;
	GLint deltaTimeLoc;

public:
	Flag(string heightmap, string texturemap, string fragmentFlag, string vertexFlag);
	CGFshader shader;
	virtual void draw(float s, float t);
	virtual void update(unsigned long t);
	unsigned long startTime;
	float dT;
}