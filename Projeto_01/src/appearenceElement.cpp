#include "appearenceElement.h"
//#include <GL\GL.h>

appearenceElement::appearenceElement()
{

}

bool appearenceElement::setElement (TiXmlElement * ele)
{
	if (ele != NULL)
	{
		element = ele;
		return true;
	} else {
		return false;
	}
}

Appearence * appearenceElement::getAppearence (std::string id)
{
	for (unsigned int app = 0; app < appearences.size(); app++)
	{
		if (id == appearences[app]->getID())
			return appearences[app];
	}

	return NULL;
}
