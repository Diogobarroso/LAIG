#include "globalElement.h"
#include <GL\GL.h>

globalElement::globalElement()
{
}

bool globalElement::setElement (TiXmlElement * ele)
{
	if (ele != NULL)
	{
		element = ele;
		return true;
	} else 
		return false;
}

bool globalElement::setDrawMode (std::string mode)
{
	if (mode == "fill") {
		drawMode = GL_FILL;
	} else if (mode == "line") {
		drawMode = GL_LINE;
	} else if (mode == "point") {
		drawMode = GL_POINT;
	} else {
		printf( "\nError parsing MODE parameter in <drawing>:\nValue must be \"fill\", \"line\", or \"point\";\n");
		return false;
	}
	return true;
}

bool globalElement::setDrawShading (std::string shading)
{
	if (shading == "flat") {
		shading = GL_FLAT;
		return true;
	} else if (shading == "gouraud") {
		shading = GL_SMOOTH;
		return true;
	} else {
		printf( "\nError parsing SHADING parameter in <drawing>:\nValue must be \"flat\" or \"gouraud\";\n");
		return false;
	}
	return true;
}

bool globalElement::setDrawBackground (float r, float g, float b, float a)
{
	if ( 0 <= r && r <= 1 && 0 <= g && g <= 1 && 0 <= b && b <= 1 && 0 <= a && a <= 1 ) {
		drawBackground = Color(r,g,b,a);
		return true;
	} else {
		printf ( "\nError parsing BACKGROUND parameter in <drawing>:\nValues must be between 0 and 1;\n");
		return false;
	}
	return true;
}

bool globalElement::setCullFace (std::string face)
{
	if (face == "none") {
		cullFace = 0;
	} else if (face == "front") {
		cullFace = GL_FRONT;
	} else if (face == "back") {
		cullFace = GL_BACK;
	} else if (face == "both") {
		cullFace = GL_FRONT_AND_BACK;
	} else {
		printf( "\nError parsing FACE parameter in <culling>:\nValue must be \"none\", \"front\", \"back\" or \"both\";\n");
		return false;
	}
	return true;
}

bool globalElement::setCullOrder (std::string order)
{
	if (order == "ccw") {
		cullOrder = GL_CCW;
	} else if (order == "cw") {
		cullOrder = GL_CW;
	} else {
		printf( "\nError parsing ORDER parameter in <culling>:\nValue must be \"ccw\" or \"cw\";\n");
		return false;
	}
	return true;
}

bool globalElement::setLightDS (std::string ds)
{
	if (ds == "true") {
		lightDoubleSided = true;
	} else if (ds == "false") {
		lightDoubleSided = false;
	} else {
		printf( "\nError parsing DOUBLESIDED parameter in <lighting>:\nValue must be \"true\" or \"false\";\n");
		return false;
	}
	return true;
}

bool globalElement::setLightLocal (std::string local)
{
	if (local == "true") {
		lightLocal = true;
	} else if (local == "false") {
		lightLocal = false;
	} else {
		printf( "\nError parsing LOCAL parameter in <lighting>:\nValue must be \"true\" or \"false\";\n");
		return false;
	}
	return true;
}

bool globalElement::setLightEnabled (std::string enable)
{
	if (enable == "true") {
		lightEnabled = true;
	} else if (enable == "false") {
		lightEnabled = false;
	} else {
		printf( "\nError parsing ENABLED parameter in <lighting>:\nValue must be \"true\" or \"false\";\n");
		return false;
	}
	return true;
}

bool globalElement::setLightAmbientColor (float r, float g, float b, float a)
{
	if ( 0 <= r && r <= 1 && 0 <= g && g <= 1 && 0 <= b && b <= 1 && 0 <= a && a <= 1 ) {
		lightAmbientColor = Color(r,g,b,a);
		return true;
	} else {
		printf ( "\nError parsing AMBIENT parameter in <lighting>:\nValues must be between 0 and 1;\n");
		return false;
	}
	return true;
}