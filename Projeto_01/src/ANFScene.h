#pragma once

#include "CGFscene.h"
#include "CGFshader.h"
#include "CGFlight.h"
#include "CGFapplication.h"

#include <algorithm>
#include <stack>

#include "tinyxml.h"

#include "globalElement.h"
#include "cameraElement.h"
#include "lightElement.h"
#include "textureElement.h"
#include "appearenceElement.h"
#include "graphElement.h"

#include "PerspectiveCamera.h"
#include "OrthoCamera.h"

#include "light.h"

#include "Appearence.h"

#include "TranslateTransformation.h"
#include "RotateTransformation.h"
#include "ScaleTransformation.h"

#include "Primitive.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Cylinder.h"
#include "Sphere.h"
#include "Torus.h"
#include "Plane.h"
#include "Patch.h"

#include "myUnitCube.h"

class ANFScene : public CGFscene
{
public:
	ANFScene(char *filename);

	void initLights();

	void init();
	void display();
	void update(unsigned long t);

	static TiXmlElement *findChildByAttribute(TiXmlElement *parent,const char * attr, const char *val);

	int * getActiveCameraIndexPointer () { return &activeCameraIndex; }
	void setActiveCameraIndex (int index) { activeCameraIndex = index;
			activeCamera = scene_cameras[index]; 
			CGFapplication::activeApp->forceRefresh();}

	void setActiveDrawMode (int index);
	int * getActiveDrawModePointer () { return &activeDrawMode; }
	int activeDrawMode;

	vector<GLuint> displayListIndexes;
	vector<graphNode *> displayListedNodes;

	std::vector<Camera *> getCameras() { return scene_cameras; }
	std::vector<light *> getLights() {return scene_lights; }
	light * getLight(int i) {return scene_lights[i]; }
	vector<int> lightsEnabled;
	~ANFScene();

protected:
	TiXmlDocument* doc;

	globalElement * global;
	cameraElement * cameras;
	textureElement * textures;
	appearenceElement * appearences;
	graphElement * graph;
	lightElement * lights;
	
	Appearence * defaultAppearence;

	bool failed;
	std::vector<std::string> usedIDs;
	std::stack<Appearence *> appearenceStack;

	std::vector<Camera *> scene_cameras;
	int activeCameraIndex;

	std::vector<light *> scene_lights;

	void processGlobal ();
	void processCameras ();
	void processLights ();
	void processTextures ();
	void processAppearences ();
	void processGraph ();

	bool generateGraph ();
	void generateMatrices (graphNode * node);
	void navigateGraph (graphNode * node);

	void generateDisplayLists();
	void messageChildren(graphNode * node);
	

};
