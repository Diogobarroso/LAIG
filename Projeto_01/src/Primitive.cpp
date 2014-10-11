#include "Primitive.h"


Primitive::Primitive(void)
{
}

Vector3 Primitive::normal( std::vector<Vector3> vertexVec )
{
	Vector3 result;

	for (unsigned int i = 0; i < vertexVec.size(); i++)
	{
		Vector3 currentVertex = vertexVec[i];
		Vector3 nextVertex = vertexVec[(i + 1) % vertexVec.size()];

		result.setX ( (currentVertex.getY() - nextVertex.getY ()) * (currentVertex.getZ() + nextVertex.getZ()) );
		result.setX ( (currentVertex.getZ() - nextVertex.getZ ()) * (currentVertex.getX() + nextVertex.getX()) );
		result.setX ( (currentVertex.getX() - nextVertex.getX ()) * (currentVertex.getY() + nextVertex.getY()) );
	}

	result.normalize();
	return result;
}

void Primitive::draw (float, float) {}

Primitive::~Primitive(void)
{
}
