#ifndef RENDERE_H
#define RENDERE_H

#include "camera.h"
#include "scene.h"

class renderer
{
private:
	camera* cam;
	scene* scn;
	std::vector<std::vector<vector>> picture;
	uint32 n;
public:
	renderer(camera* c, scene* scn);
	void Render(uint32 sampleNum);
	std::vector<std::vector<vector>>* GetPicture();
	
};



#endif