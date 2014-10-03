#include "cameraElement.h"


cameraElement::cameraElement(void)
{
	cameras = std::vector<Camera*> ();
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

Camera* cameraElement::getActiveCamera ()
{
	for (unsigned int i = 0; i < cameras.size(); i++)
	{
		if (cameras[i]->getID() == activeID)
			return cameras[i];
	}

	return NULL;

}

bool cameraElement::setActiveID (std::string id)
{
	activeID = id;
	return true;
}

bool cameraElement::setInitial (std::string id) 
{
	initial = id;
	return true;
}

void cameraElement::addCamera (Camera* camera)
{
	cameras.push_back(camera);
}

cameraElement::~cameraElement(void)
{
}
