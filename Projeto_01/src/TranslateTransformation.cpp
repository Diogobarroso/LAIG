#include "TranslateTransformation.h"


TranslateTransformation::TranslateTransformation(void)
{
}

void TranslateTransformation::apply()
{
	glTranslatef(x,y,z);
}

TranslateTransformation::~TranslateTransformation(void)
{
}
