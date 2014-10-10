#include "ScaleTransformation.h"


ScaleTransformation::ScaleTransformation(void)
{
}

void ScaleTransformation::apply ()
{
	glScalef(x,y,z);
}

ScaleTransformation::~ScaleTransformation(void)
{
}
