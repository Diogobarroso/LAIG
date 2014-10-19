#include "lightElement.h"

void lightElement::addLight(light * light)
{
	lightSet.push_back(light);
}

lightElement::lightElement() {}

bool lightElement::setElement(TiXmlElement * elem) {
	if (elem != NULL)
	{
		element = elem;
		return true;
	} else {
		return false;
	}
}

TiXmlElement * lightElement::getElement() {return element; }

vector< light * > lightElement::getLightSet() {return lightSet; }

light * lightElement::getLight(int i)
{
	return lightSet[i];
}
