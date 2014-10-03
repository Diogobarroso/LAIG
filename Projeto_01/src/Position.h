#pragma once

class Position
{
private:
	float x, y, z;
public:
	Position(void);
	Position(float, float, float);
	float getX () { return x; }
	float getY () { return y; }
	float getZ () { return z; }
};

