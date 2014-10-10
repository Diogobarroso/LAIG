#include "Texture.h"
#include <GL\GL.h>

Texture::Texture ()
{

}

void Texture::updateTexture ()
{
	texture = new CGFtexture (path);
}