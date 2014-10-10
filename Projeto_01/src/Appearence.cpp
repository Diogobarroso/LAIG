#include "Appearence.h"
#include <GL\GL.h>

Appearence::Appearence()
{
	
}

void Appearence::generateAppearence ()
{
	if (texture != NULL)
		appearence = new CGFappearance (ambient->getArray(), diffuse->getArray(), specular->getArray(), shininess);
	else
		appearence = new CGFappearance (texture->getPath(), texture->getLength_s(), texture->getLength_t());
}