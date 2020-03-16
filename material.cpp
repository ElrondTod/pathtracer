#include "material.h"
#include <cmath>

material::material(mat_type t, vector d, double r, double f, vector e)
{
	this->t = t;
	this->diffuse = d;
	this->roughness = r;
	this->F_n = f;
	this->emission = e;
}

material::material()
{
	this->t = mat_type::diffuse;
	this->diffuse = vector(1, 0, 0);
	this->roughness = 1.0;
	this->F_n = 0.8;
	this->emission = vector(0, 0, 0);
}

double material::brdf(vector N, vector L, vector V)//csak 
{
	
	return std::max(0.0, N.dot(V));
	/*
	vector H = (V + L).GetNorm();
	
	double NdotH = std::max(0.0, N.dot(H));
	double VdotH = std::max(0.0, V.dot(H));
	double NdotV = std::max(0.0, N.dot(V));
	double NdotL = std::max(0.0, N.dot(L));
	
	double F_null = (1.0 - this->F_n) / (1.0 + this->F_n);//f_n eleme 1-20
	F_null *= F_null;
	double F = F_null + (1.0 - F_null) * pow(1.0 - N.dot(V), 5.0); //jó
	
	double m2 = this->roughness * this->roughness;
	double nh2 = NdotH * NdotH;
	
	double num = nh2 - 1.0;
	double denum = nh2 * m2;
	
	double D = (exp(num / denum)) / (3.14159265 * m2 * nh2 * nh2); //jó  
	
	double g1 = (2.0 * NdotH * NdotV) / VdotH;
	double g2 = (2.0 * NdotH * NdotL) / VdotH;
	
	double G = std::min(1.0, std::min(g1, g2)); //jó
	
	return std::max((D * F * G) / (4 * NdotV * NdotL), 0.0);//D;//NdotV > 0.0 ? std::max((D * F * G) / (4.0 * NdotV * NdotL), 0.0) : 0.0;*/
}

mat_type material::GetType()
{
	return this->t;
}

vector material::GetEmission()
{
	return this->emission;
}

vector material::GetDiff()
{
	return this->diffuse;
}