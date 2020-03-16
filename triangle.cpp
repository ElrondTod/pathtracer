#include "triangle.h"

triangle::triangle(vector a, vector b, vector c, material* m)
{
	this->p0 = a;
	this->p1 = b;
	this->p2 = c;
	this->norm = ((this->p2 - this->p0).cross((this->p1 - this->p0))).GetNorm();
	this->mat = m;
}

vector triangle::GetNormal()
{
	return this->norm;
}

material* triangle::GetMaterial()
{
	return this->mat;
}

bool triangle::Between(double a)
{
	return a >= 0 && a <= 1;
}

double triangle::Intersect(ray r)
{
	vector q = this->p0;
	vector n = this->norm;

	double t = ((q - r.o).dot(n)) / (r.d.dot(n));

	if(t < 0.00001)
	{
		return -1.0;
	}
	else
	{
		vector p = r.o + r.d * t;

		vector l;
		
		if(n.x > n.y)
		{
			if(n.x > n.z)
			{
				double denom = (this->p0.z - this->p2.z) * (this->p1.y - this->p2.y) - (this->p1.z - this->p2.z) * (this->p0.y - this->p2.y);

				l.z = ((this->p1.y - this->p2.y) * (p.z - this->p2.z) - (this->p1.z - this->p2.z) * (p.y - this->p2.y)) / denom;
				l.y = (-(this->p0.y - this->p2.y) * (p.z - this->p2.z) + (this->p0.z - this->p2.z) * (p.y - this->p2.y)) / denom;
				l.x = 1 - l.z - l.y;
			}
			else
			{
				double denom = (this->p0.x - this->p2.x) * (this->p1.y - this->p2.y) - (this->p1.x - this->p2.x) * (this->p0.y - this->p2.y);

				l.x = ((this->p1.y - this->p2.y) * (p.x - this->p2.x) - (this->p1.x - this->p2.x) * (p.y - this->p2.y)) / denom;
				l.y = (-(this->p0.y - this->p2.y) * (p.x - this->p2.x) + (this->p0.x - this->p2.x) * (p.y - this->p2.y)) / denom;
				l.z = 1 - l.x - l.y;
			}
		}
		else
		{
			if(n.y > n.z)
			{
				double denom = (this->p0.x - this->p2.x) * (this->p1.z - this->p2.z) - (this->p1.x - this->p2.x) * (this->p0.z - this->p2.z);

				l.x = ((this->p1.z - this->p2.z) * (p.x - this->p2.x) - (this->p1.x - this->p2.x) * (p.z - this->p2.z)) / denom;
				l.z = (-(this->p0.z - this->p2.z) * (p.x - this->p2.x) + (this->p0.x - this->p2.x) * (p.z - this->p2.z)) / denom;
				l.y = 1 - l.x - l.z;
			}
			else
			{
				double denom = (this->p0.x - this->p2.x) * (this->p1.y - this->p2.y) - (this->p1.x - this->p2.x) * (this->p0.y - this->p2.y);

				l.x = ((this->p1.y - this->p2.y) * (p.x - this->p2.x) - (this->p1.x - this->p2.x) * (p.y - this->p2.y)) / denom;
				l.y = (-(this->p0.y - this->p2.y) * (p.x - this->p2.x) + (this->p0.x - this->p2.x) * (p.y - this->p2.y)) / denom;
				l.z = 1 - l.x - l.y;
			}
		}
		
		if(l.y> 0 && l.x > 0 && l.z > 0)
		{
			return t;
		}
	
		return -1.0;
	}
}

triangle triangle::operator+(const vector& a)
{
	return triangle(this->p0 + a, this->p1 + a, this->p2 + a, this->mat);
}
