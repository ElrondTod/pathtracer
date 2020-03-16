#include "scene.h"
#include <cfloat>
#include <iostream>
#include <stdlib.h>
#include <time.h> 
#include <cmath> 

scene::scene(uint32 d)
{
	this->maxDepth = d;
	this->objects = std::vector<object*>();
	this->k = 1;
	srand(time(NULL));
}

void scene::Add(object* o)
{
	this->objects.push_back(o);
}

vector scene::Trace(ray r, uint32 depth)
{
	if(depth > this->maxDepth)
	{
		return vector(0.0, 0.0, 0.0);
	}
	
	intersection_info t;
	intersection_info t_min;
	t_min.t = 100000000;
	
	for(uint32 i = 0;i<this->objects.size();++i)
	{
		t = this->objects[i]->CalcIntersetcion(r);

		if(t.hit && t.t < t_min.t)
		{
			t_min = t;
		}
	}
		
	if(!t_min.hit)
	{
		return vector(0.0, 0.0, 0.0);
	}
		
	//return vector(t_min.t, t_min.t, t_min.t) / 25.0;
	//return vector(fabs(t_min.normal.x), fabs(t_min.normal.y), fabs(t_min.normal.z));
	//return r.d * t_min.t;

	ray reflected_ray = math::GetReflectedRay(r.o + r.d * t_min.t, double(rand()) / RAND_MAX ,double(rand()) / RAND_MAX,/*math::CalculateNumber(this->k, 2), math::CalculateNumber(this->k, 3),*/ t_min.normal);
	
	//return vector(fabs(reflected_ray.d.x), fabs(reflected_ray.d.y), fabs(reflected_ray.d.z));
	
	this->k++;
	
	double brdf = /*std::max(0.0, t_min.normal.dot(r.d * (-1.0))) + */t_min.mat->brdf(t_min.normal, reflected_ray.d, r.d * (-1.0));//kell  diffuseés frsnel-nél 1-20 között
	
	//return vector(1.0, 0.0, 0.0) * brdf ;
	
	if(t_min.mat->GetType() == emmitter)
	{
		return t_min.mat->GetEmission();
	}
	
	double p = 2.0;//3.14159265 * 2.0;
	//double brdf = t_min.mat->brdf(t_min.normal, r.d * (-1.0), reflected_ray.d);//1.0 / 3.14159265;// + t_min.mat->brdf(t_min.normal, reflected_ray.d, r.d * (-1.0));
	double cos_theta = t_min.normal.dot(reflected_ray.d);
	
	vector incoming = Trace(reflected_ray, depth + 1);
	
	return t_min.mat->GetEmission() + (t_min.mat->GetDiff() * brdf * incoming * cos_theta * p);//t_min.mat->GetDiff() * t_min.mat->brdf(t_min.normal, reflected_ray.d, (r.d * -1.0).GetNorm());// * incoming;//t_min.mat->GetEmission() + (brdf * incoming * cos_theta / p);
}

void scene::resetk()
{
	this->k=1;
}
