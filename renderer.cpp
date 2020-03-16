#include "renderer.h"
#include <iostream>
#include <cmath>

renderer::renderer(camera* c, scene* s)
{
	this->cam = c;
	this->scn = s;

	this->picture.resize(this->cam->GetWidth());
	
	for(int i = 0;i<this->cam->GetWidth();++i)
	{
		this->picture[i].resize(this->cam->GetHeight());
	}
	
	this->n = 0;
}

void renderer::Render(uint32 sampleNum)
{
	int width = this->cam->GetWidth(), height = this->cam->GetHeight();
	
	std::cout << width << " " <<height<<std::endl;
	uint32 ps = 0;
	uint32 n = 0;
	
	for(int i = 0;i<width;i++)
	{
		for(int j = 0;j<height;j++)
		{
			vector color = vector();
		
			for(uint32 s = 0;s<sampleNum;++s)
			{		
				ray r = this->cam->GenerateRay(i, j);
				++n;
				color = color + this->scn->Trace(r, 0); 
			}
			
			this->picture[i][j] = color / (double)sampleNum;
			
			if(floor(n * 100/(width*height * sampleNum)) > ps)
			{
				std::cout << floor(n * 100/(width*height * sampleNum)) << std::endl;
				++ps;
			}
		}

	}
}

std::vector<std::vector<vector>>* renderer::GetPicture()
{
	return &(this->picture);
}