#ifndef _LIGHTEL_H_
#define _LIGHTEL_H_

#include "light.h"
#include <vector>
#include "tinyxml.h"

class lightElement {
protected:
	vector<light * > lightSet;
	TiXmlElement * element;

public:
	lightElement();
	bool setElement(TiXmlElement * elem);
	TiXmlElement * getElement();
	vector<light * > getLightSet();
	light * getLight(int i);

	void addLight(light *light);
};

#endif