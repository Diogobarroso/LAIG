#include "Texture.h"
#include <GL/gl.h>

Texture::Texture ()
{

}

void Texture::updateTexture ()
{
	texture = new CGFtexture (path);
}
