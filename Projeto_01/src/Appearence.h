#pragma once

#include <string>
#include <vector>
#include "CGFappearance.h"

#include "tinyxml.h"
#include "Color.h"
#include "Texture.h"

class Appearence
{
protected:
	std::string id, tex_id;
	float shininess;
	Texture * texture;
	Color* ambient, *diffuse, *specular;

	CGFappearance * appearence;
public:
	Appearence();

	void setID (std::string id) { this->id = id; }
	void setTexID (std::string t_id) { tex_id = t_id; }
	void setAmbient (Color * amb) { ambient = amb; }
	void setDiffuse (Color * dif) { diffuse = dif; }
	void setSpecular (Color * spec) { specular = spec; }
	void setTexture (Texture * tex) { texture = tex; }
	void setShininess (float shin) { shininess = shin; }

	std::string getID () { return id; }

	Texture * getTexture() { return texture; }

	void generateAppearence ();

	void apply () { appearence->apply(); }

};
