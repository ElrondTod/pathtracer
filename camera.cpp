#include "camera.h"
#include <cmath>

camera::camera(vector p, vector a, int w, int h)
{
	this->pos = p;
	this->at = a;//(a - p).GetNorm();
	this->up = vector(0, 1, 0);
	this->width = w;
	this->height = h;
	
	this->w = (this->pos - this->at).GetNorm();
	this->u = (this->up.cross(this->w)).GetNorm();
	this->v = this->w.cross(this->u);
	
	this->width_half = this->width / 2;
	this->height_half = this->height / 2;
	
	this->aspect_ratio = (double)w/h;
}

int camera::GetWidth()
{
	return this->width;
}

int camera::GetHeight()
{
	return this->height;
}

ray camera::GenerateRay(int i, int j)
{
	double alpha = tan(3.14159265/4.0) * (i - this->width_half) / this->width_half * this->aspect_ratio;
	double beta = tan(3.14159265/4.0) * (this->height_half - j) / this->height_half;
	
	vector p = this->pos + (u * alpha + v * beta - w);
	
	return ray(this->pos, (p - this->pos).GetNorm());
}
