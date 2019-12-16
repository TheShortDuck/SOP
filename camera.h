#ifndef CAMERAH
#define CAMERAH

#include "ray.h"

class camera {
public:
	camera() {
		lower_left_corner = vctr(-2.0, -1.0, -1.0);
		horizontal = vctr(4.0, 0.0, 0.0);
		vertical = vctr(0.0, 2.0, 0.0);
		origin = vctr(0.0, 0.0, 0.0);
	}
	ray get_ray(float u, float v) { return ray(origin, lower_left_corner + u * horizontal + v * vertical - origin); }

	vctr origin;
	vctr lower_left_corner;
	vctr horizontal;
	vctr vertical;
};

#endif

