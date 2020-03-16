#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "ray.h"
#include "material.h"

class triangle
{
private:
	vector p0, p1, p2;
	vector norm;
	material* mat;

	bool Between(double a);
public:
	triangle(vector a, vector b, vector c, material* m);
	
	vector GetNormal();
	material* GetMaterial();
	double Intersect(ray r);
	
	triangle operator+(const vector& a);
};

#endif
