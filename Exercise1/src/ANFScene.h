#ifndef _XMLSCENE_H_
#define _XMLSCENE_H_

#include "tinyxml.h"

class ANFScene
{
public:
	ANFScene(char *filename);
	~ANFScene();

	static TiXmlElement *findChildByAttribute(TiXmlElement *parent,const char * attr, const char *val);
	
protected:

	TiXmlDocument* doc;

	TiXmlElement* initElement; 
	TiXmlElement* matsElement;
	TiXmlElement* textsElement;
	TiXmlElement* leavesElement;
	TiXmlElement* nodesElement;
	TiXmlElement* graphElement;
};

#endif