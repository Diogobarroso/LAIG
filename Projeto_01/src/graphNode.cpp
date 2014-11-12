#include "graphNode.h"


graphNode::graphNode(void)
{
	primitives = std::vector <Primitive *> ();
	descendants = std::vector <graphNode *> ();
	transformations = std::vector <Transformation *> ();

	visited = false;
	displayList = false;
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
	if (! transformations.empty())
		for (unsigned int transform = 0; transform < transformations.size(); transform++)
		{
			transformations[transform]->apply();
		}
}

void graphNode::draw(float s, float t)
{
	if(displayList == -1)
		for (unsigned int primitive = 0; primitive < primitives.size(); primitive++)
		{
			primitives[primitive]->draw(s,t);
		}
	else
		glCallList(displayList);
}

void graphNode::startDisplayList()
{
	glNewList(displayList, GL_COMPILE);
	for(int i = 0; i < descendants.size(); i++)
		descendants[i]->draw(1,1);
	glEndList();
}

void graphNode::message(graphNode * parent)
{
	dListVec.push_back(make_pair(parent, -1));
}

graphNode::~graphNode(void)
{
}
