#include <iostream>
#include <fstream>
#include <float.h>
#include <stdlib.h>
#include "camera.h"
#include "hits_list.h"
#include "material.h"
#include "random.h"
#include "sphere.h"


// farve
vctr color(const ray& r, hits *world, int depth) {
	hit_record rec;
	if (world->hit(r, 0.001, FLT_MAX, rec)) {
		ray scattered;
		vctr attenuation;
		if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
			return attenuation * color(scattered, world, depth + 1);
		}
		else {
			return vctr(0, 0, 0);
		}
	}
	else {
		vctr e_direction = e_vektor(r.direction());
		float t = 0.5 * (e_direction.y() + 1.0);
		return (1.0 - t) * vctr(1.0, 1.0, 1.0) + t * vctr(0.5, 0.7, 1.0);
	}
}


int main() {
	//file save
	std::ofstream imgFile;
	imgFile.open("img.ppm", std::ios_base::trunc);

	int nx = 200;
	int ny = 100;
	int ns = 100;

	//std::cout << "P3\n" << nx << " " << ny << "\n255\n";
	imgFile << "P3\n" << nx << " " << ny << "\n255\n";

	//HER ER FORMER/PRIMITIVER
	hits* list[4];
	list[0] = new sphere(vctr(0, 0, -1), 0.5 , new lambertian(vctr(0.2, 0.2, 0.9)));
	list[1] = new sphere(vctr(0, -100.5, -1), 100, new lambertian(vctr(0.6,0.9,0.6)));
	list[2] = new sphere(vctr(1.2, 0, -1),0.5, new metal(vctr(0.8,0.8,0.8),0.6));
	list[3] = new sphere(vctr(-1.2,0,-1), 0.5, new dielectric(1.3));
	hits* world = new hits_list(list, 4);
	camera cam;

	for (int j = ny - 1; j >= 0; j--) {
		for (int i = 0; i < nx; i++) {
			vctr col(0, 0, 0);
			for (int s = 0; s < ns; s++) {
				float u = float(i + rand_double()) / float(nx);
				float v = float(j + rand_double()) / float(ny);
				ray r = cam.get_ray(u, v);
				vctr p = r.punkt_ved_para(2.0);
				col += color(r, world, 0);
			}
			col /= float(ns);
			col = vctr(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
			int ir = int(255.99 * col[0]);
			int ig = int(255.99 * col[1]);
			int ib = int(255.99 * col[2]);
			//std::cout << ir << " " << ig << " " << ib << "\n";
			imgFile<< ir << " " << ig << " " << ib << "\n";
		}
	}
	imgFile.close();
}