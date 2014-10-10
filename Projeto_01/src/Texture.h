#pragma once

#include <string>
#include "CGFtexture.h"

class Texture
{
protected:
	std::string id;
	std::string path;

	float length_s, length_t;

	CGFtexture * texture;

public:
	Texture();

	void setID (std::string id) { this->id = id; }
	void setPath (std::string path) { this->path = path; }
	void setLength_s (float l_s) { this->length_s = l_s; }
	void setLength_t (float l_t) { this->length_t = l_t; }

	std::string getID () { return id; }
	std::string getPath () { return path; }
	float getLength_s () { return length_s; }
	float getLength_t () { return length_t; }

	void updateTexture ();
	void apply () { texture->apply(); }
};

