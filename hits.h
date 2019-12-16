#ifndef HITSH
#define HITSH

#include "ray.h"

class material;

struct hit_record {
	float t;
	vctr p;
	vctr normal;
	material* mat_ptr;
};

class hits {
public:
	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
};

#endif