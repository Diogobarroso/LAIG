#ifndef _COLOR_H_
#define _COLOR_H_

class Color
{
private:
	float red, green, blue, alpha;

public:
	Color();
	Color(float red, float green, float blue, float alpha);

	float getRed();
	float getGreen();
	float getBlue();
	float getAlpha();
}

#endif