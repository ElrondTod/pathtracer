#ifndef CAMERA_H
#define CAMERA_H

#include "ray.h"

class camera
{
private:
	vector pos;
	vector at;
	vector up;
	
	int width;
	int height;
	
	vector u, v, w;
	
	double width_half, height_half;
	double aspect_ratio;
	
public:
	camera(vector p, vector a, int w, int h);
	
	int GetWidth();
	int GetHeight();
	
	ray GenerateRay(int w, int h);

};

#endif
