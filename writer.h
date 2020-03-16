#ifndef WRITER_H
#define WRITER_H

#include "vector.h"
#include <vector>
#include <fstream>

class writer
{
private:
	int width, height;
	std::string name;
	std::ofstream out;
	std::ofstream o2;
public:
	writer(int w, int h, std::string n);
	bool Write(std::vector<std::vector<vector>>* colormap);

};

#endif