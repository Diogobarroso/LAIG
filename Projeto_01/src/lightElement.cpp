#include "lightElement.h"

void lightElement::addLight(light * light)
{
	lightSet.push_back(light);
}

lightElement::lightElement() {}

bool lightElement::setElement(TiXmlElement * elem) {element = elem; return true; }

TiXmlElement * lightElement::getElement() {return element; }

vector< light * > lightElement::getLightSet() {return lightSet; }