#include "Appearence.h"
//#include <GL\GL.h>

Appearence::Appearence()
{
	texture = NULL;
}

void Appearence::generateAppearence ()
{
	if (texture == NULL)
	{
		
		float * a = ambient->getArray();
		float * d = diffuse->getArray();
		float * s = specular->getArray();
		appearence = new CGFappearance (a, d, s, shininess);
		
	}
	else
		appearence = new CGFappearance (texture->getPath(), texture->getLength_s(), texture->getLength_t());
}
