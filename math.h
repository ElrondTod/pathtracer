#ifndef MATH_H
#define MATH_H

#include "ray.h"

namespace math
{
	double CalculateNumber(int index, int base);
	ray GetReflectedRay(vector p, double z, double n, vector norm);
}

#endif