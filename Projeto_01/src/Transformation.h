#pragma once

#include "GL\gl.h"

class Transformation
{
public:
	Transformation(void);

	virtual void apply();

	~Transformation(void);
};

