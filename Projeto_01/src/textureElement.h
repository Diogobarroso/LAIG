#pragma once

#include <vector>
#include <string>

#include "tinyxml.h"
#include "Color.h"

#include "Texture.h"

class textureElement
{
protected:
	TiXmlElement * element;
	std::vector<Texture *> textures;
	
public:
	textureElement();

	bool setElement (TiXmlElement * ele);
	void addTexture (Texture * tex) { textures.push_back (tex); }

	Texture* getTexture (std::string id);

	TiXmlElement * getElement () { return element; }

};
