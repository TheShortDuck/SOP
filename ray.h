#ifndef RAYH
#define RAYH
#include "vctr.h"

class ray {
public:
	ray(){}
	ray(const vctr& a, const vctr& b) { A = a; B = b; }
	vctr origin() const { return A; }
	vctr direction() const { return B; }
	vctr punkt_ved_para(float t) const { return A + t * B; } //Parameterfremstilling linje

	vctr A;
	vctr B;
};

#endif
