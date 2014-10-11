#pragma once

#include <string>
#include <vector>
#include "CGFappearance.h"
#include <map>
#include "Appearence.h"
#include "tinyxml.h"
#include "Color.h"

class appearenceElement
{
protected:
	TiXmlElement * element;
	std::vector <Appearence *> appearences;


public:
	appearenceElement();

	bool setElement (TiXmlElement * ele);

	void addAppearence (Appearence * app) { appearences.push_back(app); }

	Appearence * getAppearence (std::string id);

	TiXmlElement * getElement () { return element; }

};
