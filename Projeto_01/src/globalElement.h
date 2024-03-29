#pragma once

#include <string>

#include "tinyxml.h"
#include "Color.h"

class globalElement
{
protected:
	TiXmlElement * element;

	int drawMode;
	int drawShading;
	Color drawBackground;
	
	int cullFace;
	int cullOrder;

	bool lightDoubleSided;
	bool lightLocal;
	bool lightEnabled;
	Color lightAmbientColor;

public:
	globalElement();

	bool setElement (TiXmlElement * ele);

	bool setDrawMode (std::string mode);
	bool setDrawShading (std::string shading);
	bool setDrawBackground (float r, float g, float b, float a);

	bool setCullFace (std::string face);
	bool setCullOrder (std::string order);

	bool setLightDS (std::string ds);
	bool setLightLocal (std::string local);
	bool setLightEnabled (std::string enable);
	bool setLightAmbientColor (float r, float g, float b, float a);

	TiXmlElement * getElement () { return element; }

	int getDrawMode () { return drawMode; }
	int getDrawShading () { return drawShading; }
	Color getDrawBackground () { return drawBackground; }

	int getCullFace () { return cullFace; }
	int getCullOrder () { return cullOrder; }

	bool getLightDS () { return lightDoubleSided; }
	bool getLightLocal () { return lightLocal; }
	bool getLightEnabled () { return lightEnabled; }
	Color getLightAmbientColor () { return lightAmbientColor; }
};
