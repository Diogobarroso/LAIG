#include "appearenceElement.h"
#include <GL\GL.h>

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
