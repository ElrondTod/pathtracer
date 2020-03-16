#include "math.h"
#include <cmath>


double math::CalculateNumber(int index, int base)
{
	double result = 0.0;
	double f = 1.0;

	while(index > 0)
	{
		f = f / base;
		result = result + f * (index % base);
		index = (index / base);
	}
	return result;
}

ray math::GetReflectedRay(vector p, double z, double n, vector norm)
{
	double theta = 2.0 * n * 3.14159265;
	z = z * 2.0 - 1.0;
	
	vector d;
	d.z = z;
	d.x = cos(theta);
	d.y = sin(theta);
	
	vector dir = (d - norm * d.dot(norm) + norm * fabs(d.dot(norm))).GetNorm();
	
	return ray(p + dir * 0.001, dir);//normál irányába eltolni
}
