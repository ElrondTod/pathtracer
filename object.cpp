#include "object.h"
#include <cmath>

intersection_info::intersection_info()
{
	this->hit = false;
	this->t = -1.0; //float_max
	this->normal = vector();
	this->mat = NULL;
}

intersection_info& intersection_info::operator=(const intersection_info& a)
{
	this->hit = a.hit;
	this->t = a.t;
	this->normal = a.normal;
	this->mat = a.mat;
	
	return *this;
}

object::~object()
{
	
}

sphere::sphere(vector c, double r, material* m)
{
	this->pos = c;
	this->radius = r;
	this->mat = m;
}

sphere::~sphere()
{

}

double sphere::GetR()
{
	return this->radius;
}

vector sphere::GetPos()
{
	return this->pos;
}

material sphere::GetMaterial()
{
	return *(this->mat);
}

vector sphere::CalcNormal(vector p)
{
	return (p - this->pos).GetNorm();
}

intersection_info sphere::CalcIntersetcion(ray r)
{
	intersection_info result;
	
	double disc;

	double a = r.d.dot(r.d);
	double b = r.d.dot(r.o - this->pos) * 2.0;
	double c = (r.o - this->pos).dot(r.o - this->pos) - (this->radius * this->radius);

	disc = b * b - 4.0 * a * c;

	if(disc >= 0.0001)
	{
		result.hit = true;
		result.mat = this->mat;
		
		double t1, t2;
		t1 = (-b + std::sqrt(disc)) / (2 * a);
		t2 = (-b - std::sqrt(disc)) / (2 * a);
		
		if(t1 > 0.0 && t2 > 0.0)
		{
			result.t = t1 > t2  ? t2 : t1;
		}
		else if(t1 > 0.0 && t2 < 0.0)
		{
			result.t = t1;
		}
		else if(t1 < 0.0 && t2 > 0.0)
		{
			result.t = t1;
		}
		else
		{
			result.hit = false;
		}

		result.normal = this->CalcNormal(r.o + r.d * result.t);
	}
	
	return result;
}

shape::shape(vector p)
{
	this->pos = p;
}

shape::~shape()
{

}

void shape::Add(triangle t)
{
	this->triangles.push_back(t + this->pos);
}

vector shape::GetPos()
{
	return this->pos;
}

material shape::GetMaterial(int i)
{
	return *(this->triangles[i].GetMaterial());
}

intersection_info shape::CalcIntersetcion(ray r)
{
	intersection_info t;
	double inters;
	double inters_min = 1000000;
	
	uint32 i;
	uint32 index_min;
	
	for(i = 0;i<this->triangles.size();++i)
	{
		inters = this->triangles[i].Intersect(r);
		
		if(inters != -1.0 && inters < inters_min)
		{
			inters_min = inters;
			index_min = i;
			t.hit = true;
		}
		
	}

	if(t.hit)
	{
		t.t = inters;
		t.normal = this->triangles[index_min].GetNormal();
		t.mat = this->triangles[index_min].GetMaterial();
	}
	
	return t;
}

plane::plane(vector c, vector n, material* m)
{
	this->pos = c;
	this->n = n;
	this->mat = m;
}

plane::~plane()
{
	
}

intersection_info plane::CalcIntersetcion(ray r)
{
	intersection_info result;
	
	double t = this->n.dot(this->pos - r.o) / this->n.dot(r.d);

	if(t > 0.0001)
	{
		result.hit = true;
		result.t = t;
		result.normal = this->n;
		result.mat = this->mat;
	}
	
	return result;
}

vector plane::GetPos()
{
	return this->pos;
}

material plane::GetMaterial()
{
	return *(this->mat);
}

