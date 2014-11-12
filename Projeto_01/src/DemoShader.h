#ifndef _DEMO_SHADER_H_
#define _DEMO_SHADER_H_

#include "CGFshader.h"
#include "CGFtexture.h"


class DemoShader :	public CGFshader
{
public:
	DemoShader();
	virtual void bind(void);
	~DemoShader(void);
	void setScale(float s);
	float normScale;

protected:
	CGFtexture * baseTexture;
	CGFtexture * secTexture;

	GLint baseImageLoc;
	GLint secImageLoc;

	GLint scaleLoc;
};

#endif // _DEMO_SHADER_H_