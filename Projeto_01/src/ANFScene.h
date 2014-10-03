#ifndef _ANFSCENE_H_
#define _ANFSCENE_H_

#include "CGFscene.h"
#include "CGFshader.h"

#include <algorithm>

#include "tinyxml.h"

#include "globalElement.h"
#include "cameraElement.h"

#include "PerspectiveCamera.h"
#include "OrthoCamera.h"

#include "myUnitCube.h"

class ANFScene : public CGFscene
{
public:
	ANFScene(char *filename);

	void initCameras();
	void setCamera(Camera cam);

	void init();
	void display();
	void update(unsigned long t);

	static TiXmlElement *findChildByAttribute(TiXmlElement *parent,const char * attr, const char *val);

	~ANFScene();

protected:
	TiXmlDocument* doc;

	globalElement global;
	cameraElement cameras;
	
	//Camera * activeCamera;
	std::vector<std::string> usedIDs;
	/*
	TiXmlElement* initElement; 
	TiXmlElement* matsElement;
	TiXmlElement* textsElement;
	TiXmlElement* leavesElement;
	TiXmlElement* nodesElement;
	TiXmlElement* graphElement;
	*/

	/* Testing */

	CGFlight* light0;
	myUnitCube* cube;

};

#endif