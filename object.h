#ifndef OBJECT_H
#define OBJECT_H

#include "triangle.h"
#include <vector>

struct intersection_info
{
	bool hit;
	double t;
	vector normal;
	material* mat;
	
	intersection_info();
	intersection_info& operator=(const intersection_info& a);
};

class object
{
public:
	vector pos;
	virtual ~object() = 0;
	virtual intersection_info CalcIntersetcion(ray r) = 0;
	virtual vector GetPos() = 0;
};

class sphere : public object
{
private:
	double radius;
	material* mat;
	vector CalcNormal(vector p);
public:
	sphere(vector c, double r, material* m);
	~sphere();
	double GetR();
	vector GetPos();
	material GetMaterial();

	intersection_info CalcIntersetcion(ray r);
};

class shape : public object
{
private:
	std::vector<triangle> triangles;
public:
	shape(vector p);
	~shape();

	void Add(triangle t);


	vector GetPos();
	material GetMaterial(int i);

	intersection_info CalcIntersetcion(ray r);
};

class plane : public object
{
private:
	vector n;
	material* mat;
public:
	plane(vector c, vector n, material* m);
	~plane();
	intersection_info CalcIntersetcion(ray r);
	
	vector GetPos();
	material GetMaterial();
};

#endif
