#ifndef SCENE_H
#define SCENE_H

#include "object.h"
#include "math.h"

class scene
{
private:
	std::vector<object*> objects;
	uint32 maxDepth;
	int k;
public:
	scene(uint32 d);
	void Add(object* o);
	vector Trace(ray r, uint32 depth);
	vector TraceLight(ray r);
	void resetk();
};

#endif
