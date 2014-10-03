#pragma once

#include <vector>
#include <string>
#include "tinyxml.h"

#include "Camera.h"

class cameraElement
{
private:
	TiXmlElement * element;

	std::vector<Camera*> cameras;

	std::string initial;
	std::string activeID;
public:
	cameraElement(void);

	bool setElement (TiXmlElement * ele);
	bool setInitial (std::string id);
	bool setActiveID (std::string id);
	
	TiXmlElement * getElement () { return element; }

	std::string getInitial () { return initial; }
	std::vector<Camera*> getCameras () { return cameras; }
	std::string getActiveID () { return activeID; }

	Camera* getActiveCamera ();

	void addCamera (Camera* camera);

	~cameraElement(void);
};

