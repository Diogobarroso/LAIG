#ifndef _ANFSCENE_H_
#define _ANFSCENE_H_

#include "CGFscene.h"
#include "CGFshader.h"

#include "tinyxml.h"

#include "globalElement.h"

class ANFScene : public CGFscene
{
public:
	ANFScene(char *filename);

	void init();
	void display();
	void update(unsigned long t);

	static TiXmlElement *findChildByAttribute(TiXmlElement *parent,const char * attr, const char *val);
	
	~ANFScene();

protected:
	TiXmlDocument* doc;

	globalElement global;

	TiXmlElement* initElement; 
	TiXmlElement* matsElement;
	TiXmlElement* textsElement;
	TiXmlElement* leavesElement;
	TiXmlElement* nodesElement;
	TiXmlElement* graphElement;

};

#endif