#include "Torus.h"

double const pi = acos(-1.0);

Torus::Torus(void)
{
}

void Torus::draw(float, float)
{
	for (unsigned int s = 0; s < vertices.size(); s++)
	{
		for (unsigned int l = 0; l < vertices[s].size(); l++)
		{
			glBegin(GL_QUADS);
			int sIndex = s, lIndex = l;

			std::vector <Vector3> quad;
			quad.push_back(vertices[sIndex][lIndex]);
			sIndex = (++ sIndex) % slices;
			quad.push_back(vertices[sIndex][lIndex]);
			lIndex = (++ lIndex) % loops;
			quad.push_back(vertices[sIndex][lIndex]);
			sIndex = s;
			quad.push_back(vertices[sIndex][lIndex]);

			Vector3 n;
			n = normal(quad);

			glNormal3f(n.getX(), n.getY(), n.getZ());

			for (unsigned int i = 0; i < quad.size(); i++)
				glVertex3f(quad[i].getX(), quad[i].getY(), quad[i].getZ());

			glEnd();
		}
	}
}

void Torus::generateVertices()
{
	Vector3 center = Vector3(0,0,0);
	Vector3 Z = Vector3(0,0,1);
	float uInc = 2*pi/slices;
	float vInc = 2*pi/loops;
	float u = 0;
	for (unsigned int s = 0; s < slices; s++)
	{
		Vector3 P = center + Vector3(cos(u), sin(u), 0) * innerRadius;

		std::vector <Vector3> circle;
		float v = 0;
		for (unsigned int l = 0; l < loops; l++)
		{
			Vector3 W = P - center;
			W.normalize();

			Vector3 Q = P + (W * outerRadius * cos(v)) + (Z * outerRadius * sin (v));

			circle.push_back(Q);

			v += vInc;
		}

		vertices.push_back(circle);

		u += uInc;
	}
}

Torus::~Torus(void)
{
}
