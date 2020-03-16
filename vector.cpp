#include "vector.h"
#include <cmath>

vector::vector(double x, double y, double z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

vector::vector()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

vector vector::operator+(const vector& a)
{
	return vector(this->x + a.x, this->y + a.y, this->z + a.z);	
}

vector vector::operator*(const double a)
{
	return vector(this->x * a, this->y * a, this->z * a);	
}

vector vector::operator*(const vector& a)
{
	return vector(this->x * a.x, this->y * a.z, this->z * a.z);	
}

vector vector::operator/(const double a)
{
	return vector(this->x / a, this->y / a, this->z / a);
}

vector vector::operator-(const vector& a)
{
	return vector(this->x - a.x, this->y - a.y, this->z - a.z);
}

vector vector::cross(vector b)
{
	double i = this->y * b.z - this->z * b.y;
	double j = -1 * (this->x * b.z - this->z * b.x);
	double k = this->x * b.y - this->y * b.x;

	return vector(i, j, k);
}

double vector::dot(vector a)
{
	return (this->x * a.x + this->y * a.y + this->z * a.z);	
}

void vector::Normalize()
{
	*this = *this / Length();
}

vector vector::GetNorm()
{
	return (Length() == 0 ? *this : *this / Length());
}

double vector::Length()
{	
	return std::sqrt((*this).dot(*this));
}

uint16* vector::ToInt()
{
	this->rgb[0] = floor(this->x >= 1.0 ? 65535 : this->x * 65535);
	this->rgb[1] = floor(this->y >= 1.0 ? 65535 : this->y * 65535);
	this->rgb[2] = floor(this->z >= 1.0 ? 65535 : this->z * 65535);
	
	return this->rgb;
}
