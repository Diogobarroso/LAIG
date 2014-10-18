#include "cameraElement.h"


cameraElement::cameraElement(void)
{
}

bool cameraElement::setElement (TiXmlElement * ele)
{
	if (ele != NULL)
	{
		element = ele;
		return true;
	} else {
		return false;
	}
}

bool cameraElement::setInitial (std::string id) 
{
	initial = id;
	return true;
}


cameraElement::~cameraElement(void)
{
}
