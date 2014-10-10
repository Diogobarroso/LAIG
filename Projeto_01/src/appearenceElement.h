#pragma once

#include <string>
#include <vector>
#include "CGFappearance.h"
#include <map>

#include "tinyxml.h"
#include "Color.h"

class appearenceElement
{
protected:
	TiXmlElement * element;
	std::vector <CGFappearance *> appearences;


public:
	appearenceElement();

	bool setElement (TiXmlElement * ele);

	TiXmlElement * getElement () { return element; }

};
