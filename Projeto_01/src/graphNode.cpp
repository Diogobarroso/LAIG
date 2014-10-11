#include "graphNode.h"


graphNode::graphNode(void)
{
	primitives = std::vector <Primitive *> ();
	descendants = std::vector <graphNode *> ();
	transformations = std::vector <Transformation *> ();

	visited = false;
}

bool graphNode::setElement (TiXmlElement * ele)
{
	if (ele != NULL)
	{
		element = ele;
		return true;
	} else 
		return false;
}

void graphNode::setID (std::string id)
{
	this->id = id;
}

void graphNode::applyTransforms ()
{
	for (unsigned int transform = 0; transform < transformations.size(); transform++)
	{
		transformations[transform]->apply();
	}
}

void graphNode::draw(float s, float t)
{
	for (unsigned int primitive = 0; primitive < primitives.size(); primitive++)
	{
		primitives[primitive]->draw(s,t);
	}
}

graphNode::~graphNode(void)
{
}
