#pragma once

#include "CGFscene.h"
#include "CGFshader.h"
#include "CGFlight.h"

#include <algorithm>

#include "tinyxml.h"

#include "globalElement.h"
#include "cameraElement.h"
#include "lightElement.h"
#include "textureElement.h"
#include "appearenceElement.h"
#include "graphElement.h"

#include "PerspectiveCamera.h"
#include "OrthoCamera.h"

#include "omnilight.h"
#include "spotlight.h"

#include "Appearence.h"

#include "TranslateTransformation.h"
#include "RotateTransformation.h"
#include "ScaleTransformation.h"

#include "Primitive.h"
#include "Rectangle.h"
#include "Triangle.h"

#include "myUnitCube.h"

class ANFScene : public CGFscene
{
public:
	ANFScene(char *filename);

	void initCameras();
	void setCamera(Camera cam);

	void initLights();

	void init();
	void display();
	void update(unsigned long t);

	static TiXmlElement *findChildByAttribute(TiXmlElement *parent,const char * attr, const char *val);

	~ANFScene();

protected:
	TiXmlDocument* doc;

	globalElement * global;
	cameraElement * cameras;
	textureElement * textures;
	appearenceElement * appearences;
	graphElement * graph;
	lightElement lights;
	
	/* Testing */

	CGFlight* light0;
	myUnitCube* cube;


	bool failed;
	std::vector<std::string> usedIDs;

	void processGlobal ();
	void processCameras ();
	void processTextures ();
	void processAppearences ();
	void processGraph ();

	bool generateGraph ();
	void navigateGraph (graphNode * node);

};
