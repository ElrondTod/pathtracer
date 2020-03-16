#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>

typedef unsigned short int uint16;
typedef unsigned int uint32;

struct vector
{
	double x;
	double y;
	double z;
	uint16 rgb[3];

	vector(double x, double y, double z);
	vector();
	
	uint16* ToInt();
	
	vector operator+(const vector& a);
	vector operator*(const double a);
	vector operator*(const vector& a);
	vector operator/(const double a);
	vector operator-(const vector& a);
	
	friend std::ostream& operator<<(std::ostream& o, const vector& a)
	{
		o << a.x << " " << a.y << " " << a.z;
		return o;
	}
	
	vector cross(vector b);
	double dot(vector a);

	void Normalize();
	vector GetNorm();
	double Length();
	
};

#endif
