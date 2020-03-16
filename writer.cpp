#include "writer.h"
#include "iostream"

writer::writer(int w, int h, std::string n)
{
	this->width = w;
	this->height = h;
	this->name = n;
	
	this->out.open(this->name);
	this->o2.open("test.txt");
}

bool writer::Write(std::vector<std::vector<vector>>* colormap)
{
	if(this->out.is_open())
	{
		this->out << "P3" << std::endl;
		this->out << this->width << " " << this->height << std::endl;
		this->out << 65535 << std::endl;
		
		for(int i = 0;i<this->height;++i)
		{
			for(int j = 0;j<this->width;++j)
			{	
				//std::cout << (*colormap)[j][i]<<std::endl;
				
				uint16* intColor = (*colormap)[j][i].ToInt();
				
				//std::cout << intColor[0] << " " << intColor[1] << " " << intColor[2] <<std::endl;
				
				this->out << " " << intColor[0] << " " << intColor[1] << " " << intColor[2] << " ";
				this->o2 << (*colormap)[j][i].x << " " << (*colormap)[j][i].y << " " << (*colormap)[j][i].z << "      ";
			}
			this->out << std::endl;
			this->o2 << std::endl;
		}
		
		this->out.close();
		
		return true;
	}
	else
	{
		return false;
	}
}
