#include "graphElement.h"


graphElement::graphElement(void)
{
}


bool graphElement::setElement (TiXmlElement * ele)
{
	if (ele != NULL)
	{
		element = ele;
		return true;
	} else 
		return false;
}


bool graphElement::setRootID (std::string rID)
{
	rootID = rID;
	return true;
}

graphNode* graphElement::getNode (std::string id)
{
	for (unsigned int i = 0; i < nodes.size(); i++)
	{
		if (id == nodes[i]->getID())
			return nodes[i];
	}
}

graphElement::~graphElement(void)
{
}
