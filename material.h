#ifndef MATERIAL_H
#define MATERIAL_H

#include "vector.h"

enum mat_type
{
	diffuse,
	specular,
	emmitter,
	transparent
};

class material
{
private:
	mat_type t;
	vector diffuse;
	double k;
	double roughness;
	double F_n;
	
	vector emission;
public:
	material(mat_type t, vector d, double r, double f, vector e);
	material();
	
	mat_type GetType();
	vector GetEmission();
	vector GetDiff();
	
	double brdf(vector N, vector L, vector V);
};




#endif
