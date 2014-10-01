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
	} else {
		return false;
	}
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
		printf( "\nError parsing SHADING parameter in <drawing>:\nValue must be \"flat\" or \"gourad\";\n");
		return false;
	}
}


bool globalElement::setDrawBackground (float r, float g, float b, float a)
{
	if ( 0 <= r && r <= 1 && 0 <= g && g <= 1 && 0 <= b && b <= 1 && 0 <= a && a <= 1 ) {
		drawBackground = Color(r,g,b,a);

		/* DEBUG */
		printf(" R: %f G: %f B: %f A: %f\n", r, g, b, a);

		return true;
	} else {
		printf ( "\nError parsing BACKGROUND parameter in <drawing>:\nValues must be between 0 and 1;\n");
		return false;
	}
}

/*
bool globalElement::setCullFace (std::string face)
{

}

bool globalElement::setCullOrder (std::string order);

bool globalElement::setLightDS (std::string ds);
bool globalElement::setLightLocal (std::string local);
bool globalElement::setLightAmbientColor (float r, float g, float b, float a);

*/