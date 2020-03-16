#ifndef RAY_H
#define RAY_H

#include "vector.h"

struct ray
{
	vector o;
	vector d;
	
	ray(vector o, vector d)
	{
	this->o = o;
	this->d = d;	
	}
};

#endif