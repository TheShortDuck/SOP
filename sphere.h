#ifndef SPHEREH
#define SPHEREH

#include "hits.h"


class sphere: public hits {
public:
 	sphere() {}
	sphere(vctr cen, float r, material *m) : center(cen), radius(r), mat_ptr(m) {};
	virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const;
	vctr center;
	float radius;
	material *mat_ptr;
};

bool sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
	vctr oc = r.origin() - center;
	float a = prik(r.direction(), r.direction());
	float b = prik(oc, r.direction());
	float c = prik(oc, oc) - radius * radius;
	float discriminant = b * b - a * c;
	if (discriminant > 0) {
		float temp = (-b - sqrt(discriminant)) / a;
		if (temp < t_max && temp > t_min) {
			rec.t = temp;
			rec.p = r.punkt_ved_para(rec.t);
			rec.normal = (rec.p - center) / radius;
			rec.mat_ptr = mat_ptr;
			return true;
		}
		temp = (-b + sqrt(discriminant)) / a;
		if (temp <t_max && temp >t_min) {
			rec.t = temp;
			rec.p = r.punkt_ved_para(rec.t);
			rec.normal = (rec.p - center) / radius;
			rec.mat_ptr = mat_ptr;
			return true;
		}
	}
	return false;
}

#endif
