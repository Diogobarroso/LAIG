#include "globalElement.h"
#include <GL/gl.h>
#include "textureElement.h"

textureElement::textureElement()
{

}

bool textureElement::setElement (TiXmlElement * ele)
{
	if (ele != NULL)
	{
		element = ele;
		return true;
	} else {
		return false;
	}
}

Texture * textureElement::getTexture (std::string id)
{
	for (unsigned int tex = 0; tex < textures.size(); tex++)
	{
		if (textures[tex]->getID() == id)
			return textures[tex];
	}
	return NULL;
}
