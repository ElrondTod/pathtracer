#include "renderer.h"
#include "writer.h"
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{	
	int samples = 4;
	std::string n = "output.ppm";

	if (argc == 2)
	{
		samples = atoi(argv[1]);
	}
	else if(argc == 3)
	{
		samples = atoi(argv[1]);
		n = argv[2];	
	}

	camera cam = camera(vector(0.0, 9.0, 8.99), vector(0.0, 9.0, 0), 256, 256);
    scene scn = scene(4);
	
	material light_mat = material(emmitter, vector(1.0, 1.0, 1.0), 1.0, 2.0, vector(3.0, 3.0, 3.0));
	material white = material(diffuse, vector(1.0, 1.0, 1.0), 1.0, 2.0, vector(0.0, 0.0, 0.0));
	material red = material(diffuse, vector(1.0, 0.0, 0.0), 1.0, 2.0, vector(0.0, 0.0, 0.0));
	material green = material(diffuse, vector(0.0, 1.0, 0.0), 1.0, 2.0, vector(0.0, 0.0, 0.0));
	material sphere_m = material(diffuse, vector(0.0, 1.0, 1.0), 0.0, 2.0, vector(0.0, 0.0, 0.0));
	
	
	sphere s = sphere(vector(0, 9.0, 0), 2.0, &sphere_m);
	
	shape light = shape(vector(0, 6.0, 0));

	light.Add(triangle(vector(-2.0, 0.0, 2.0), vector(-2.0, 0.0, -2.0), vector(2.0, 0.0, -2.0), &light_mat));
	light.Add(triangle(vector(-2.0, 0.0, 2.0), vector( 2.0, 0.0, -2.0), vector(2.0, 0.0,  2.0), &light_mat));
	
	plane bottom = plane(vector(0, 0, 0), vector(0, 1, 0), &white);
	plane top = plane(vector(0, 18, 0), vector(0, -1, 0), &light_mat);
	plane front = plane(vector(0, 0, -9), vector(0, 0, 1), &white);
	plane back = plane(vector(0, 0, 9), vector(0, 0, -1), &white);
	plane right = plane(vector(-9, 0, 0), vector(1, 0, 0), &red);
	plane left = plane(vector(9, 0, 0), vector(-1, 0, 0), &green);
	
	scn.Add(dynamic_cast<object*> (&bottom));
	scn.Add(dynamic_cast<object*> (&top));
	scn.Add(dynamic_cast<object*> (&back));
	scn.Add(dynamic_cast<object*> (&front));
	scn.Add(dynamic_cast<object*> (&right));
	scn.Add(dynamic_cast<object*> (&left));
	scn.Add(dynamic_cast<object*> (&s));
	//scn.Add(dynamic_cast<object*> (&light));
	
	renderer ren = renderer(&cam, &scn);
	
	ren.Render(samples);
	
	writer w = writer(cam.GetWidth(), cam.GetHeight(), n);
	w.Write(ren.GetPicture());
		
	return 0;
}