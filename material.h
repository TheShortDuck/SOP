#ifndef MATERIALH
#define MATERIALH

#include "hits.h"
#include "ray.h"
#include "random.h"

float schlick(float cosine, float ref_idx) {
	float r0 = (1 - ref_idx) / (1 + ref_idx);
	r0 = r0 * r0;
	return r0 + (1 - r0) * pow((1 - cosine), 5);
}

bool refract(const vctr& v, const vctr& n, float ni_over_nt, vctr& refracted) {
	vctr ev = e_vektor(v);
	float pk = prik(ev, n);
	float discriminant = 1.0 - ni_over_nt * ni_over_nt * (1 - pk * pk);
	if (discriminant > 0) {
		refracted = ni_over_nt * (ev - n * pk) - n * sqrt(discriminant);
		return true;
	}
	else {
		return false;
	}
}

vctr reflect(const vctr& v, const vctr& n) {
	return v - 2 * prik(v, n) * n;
}

vctr rand_in_e_sphere() {
	vctr p;
	do {
		p = 2.0 * vctr(rand_double(),rand_double(),rand_double()) - vctr(1, 1, 1);
	} while (p.kva_laengde() >= 1.0);
	return p;
}

class material {
public:
	virtual bool scatter(const ray& r_in, const hit_record& rec, vctr& attenuation, ray& scattered) const = 0;
};

class lambertian : public material {
public:
	lambertian(const vctr& a) : albedo(a){}
	virtual bool scatter(const ray& r_in, const hit_record& rec, vctr& attenuation, ray& scattered) const {
		vctr target = rec.p + rec.normal + rand_in_e_sphere();
		scattered = ray(rec.p, target - rec.p);
		attenuation = albedo;
		return true;
	}
	vctr albedo;
};

class metal : public material {
public:
	metal(const vctr& a, float f) : albedo(a) { if (f < 1)fuzz = f; else fuzz = 1; }
	virtual bool scatter(const ray& r_in, const hit_record& rec, vctr& attenuation, ray& scattered) const {
		vctr reflected = reflect(e_vektor(r_in.direction()), rec.normal);
		scattered = ray(rec.p, reflected + fuzz*rand_in_e_sphere());
		attenuation = albedo;
		return (prik(scattered.direction(), rec.normal) > 0);
	}
	vctr albedo;
	float fuzz;
};

class dielectric : public material {
public:
	dielectric(float ri) : ref_idx(ri){}
	virtual bool scatter(const ray& r_in, const hit_record& rec, vctr& attenuation, ray& scattered) const {
		vctr outward_normal;
		vctr reflected = reflect(r_in.direction(), rec.normal);
		float ni_over_nt;
		attenuation = vctr(1.0, 1.0, 1.0); //intensitetstab af lys eksisterer ikke for dielectrics
		vctr refracted;
		float reflect_prob;
		float cosine;
		if (prik(r_in.direction(), rec.normal) > 0) {
			outward_normal = -rec.normal;
			ni_over_nt = ref_idx;
			cosine = ref_idx * prik(r_in.direction(), rec.normal) / r_in.direction().laengde();
		}
		else {
			outward_normal = rec.normal;
			ni_over_nt = 1.0 / ref_idx;
			cosine = -prik(r_in.direction(), rec.normal) / r_in.direction().laengde();
		}
		if (refract(r_in.direction(), outward_normal, ni_over_nt, refracted)) {

			reflect_prob = schlick(cosine, ref_idx);
		}
		else {
			scattered = ray(rec.p, reflected);
			reflect_prob = 1.0;
		}
		if (rand_double() < reflect_prob) {
			scattered = ray(rec.p, reflected);
		}
		else {
			scattered = ray(rec.p, refracted);
		}
		return true;
	}
	float ref_idx;
};

#endif
