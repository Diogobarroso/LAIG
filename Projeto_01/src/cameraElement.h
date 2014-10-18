#pragma once

#include <vector>
#include <string>
#include "tinyxml.h"

#include "Camera.h"

class cameraElement
{
private:
	TiXmlElement * element;


	std::string initial;
	std::string activeID;
public:
	cameraElement(void);

	bool setElement (TiXmlElement * ele);
	bool setInitial (std::string id);
	bool setActiveID (std::string id);

	TiXmlElement * getElement () { return element; }
	
	// Water Line ----------------------------------


	std::string getInitial () { return initial; }
	std::string getActiveID () { return activeID; }


	~cameraElement(void);
};

