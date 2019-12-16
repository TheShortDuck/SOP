#ifndef VCTRH
#define VCTRH

#include <math.h>
#include <stdlib.h>
#include <iostream>

class vctr {
public:
	vctr(){}
	vctr(float e0, float e1, float e2) { e[0] = e0; e[1] = e1; e[2] = e2; }
	inline float x() const { return e[0]; } //koodinater
	inline float y() const { return e[1]; }
	inline float z() const { return e[2]; }
	inline float r() const { return e[0]; } //farveværdier
	inline float g() const { return e[1]; }
	inline float b() const { return e[2]; }

	inline const vctr& operator+() const { return *this; }
	inline vctr operator-() const { return vctr(-e[0], -e[1], -e[2]); }
	inline float operator[](int i) const { return e[i]; };
	inline float& operator[](int i) { return e[i]; };

	inline vctr& operator+=(const vctr& v2);
	inline vctr& operator-=(const vctr& v2);
	inline vctr& operator*=(const vctr& v2);
	inline vctr& operator/=(const vctr& v2);
	inline vctr& operator*=(const float t);
	inline vctr& operator/=(const float t);

	//længde vektor
	inline float laengde() const {
		return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
	}
	//kvardreret længde vektor
	inline float kva_laengde() const {
		return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
	}
	inline void lav_e_vektor(); //enhedsvektor

	float e[3];
};

inline std::istream& operator>>(std::istream& is, vctr& t) {
	is >> t.e[0] >> t.e[1] >> t.e[2];
	return is;
}

inline std::ostream& operator<<(std::ostream& os, const vctr& t) {
	os << t.e[0] << " " << t.e[1] << " " << t.e[2];
	return os;
}
// funktion til at gøre til enhedsvektor
inline void vctr::lav_e_vektor() {
	float k = 1.0 / sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
	e[0] *= k; e[1] *= k; e[2] *= k;
}

//funktion til sammenlægning med vektorer
inline vctr operator+(const vctr& v1, const vctr& v2) {
	return vctr(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
}
//funktion til subtraktion mellem vektorer
inline vctr operator-(const vctr& v1, const vctr& v2) {
	return vctr(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
}
//funktion multiplikation vektorer
inline vctr operator*(const vctr& v1, const vctr& v2) {
	return vctr(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]);
}
//funktion division med vektorer
inline vctr operator/(const vctr& v1, const vctr& v2) {
	return vctr(v1.e[0] / v2.e[0], v1.e[1] / v2.e[1], v1.e[2] / v2.e[2]);
}
//funktion multiplikation med t
inline vctr operator*(float t, const vctr &v) {
	return vctr(t*v.e[0], t*v.e[1], t*v.e[2]);
}
inline vctr operator*(const vctr &v, float t) {
	return vctr(t * v.e[0], t * v.e[1], t * v.e[2]);
}
//division af vektor med t
inline vctr operator/(vctr v, float t) {
	return vctr(v.e[0] / t, v.e[1] / t, v.e[2] / t);
}
//funktion prikprodukt af to vektorer
inline float prik(const vctr& v1, const vctr& v2) {
	return v1.e[0] * v2.e[0] + v1.e[1] * v2.e[1] + v1.e[2] * v2.e[2];
}
//krydsprodukt mellem to vektorer
inline vctr kryds(const vctr& v1, const vctr& v2) {
	return vctr(v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1],
				-(v1.e[0] * v2.e[2] - v1.e[2] * v2.e[0]),
				v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0]);
}

//funktion +=
inline vctr& vctr::operator+=(const vctr &v) {
	e[0] += v.e[0];
	e[1] += v.e[1];
	e[2] += v.e[2];
	return *this;
}
//funktion *=
inline vctr& vctr::operator*=(const vctr &v) {
	e[0] *= v.e[0];
	e[1] *= v.e[1];
	e[2] *= v.e[2];
	return *this;
}
//funktion /=
inline vctr& vctr::operator/=(const vctr &v) {
	e[0] /= v.e[0];
	e[1] /= v.e[1];
	e[2] /= v.e[2];
	return *this;
}
//funktion -=
inline vctr& vctr::operator-=(const vctr& v) {
	e[0] -= v.e[0];
	e[1] -= v.e[1];
	e[2] -= v.e[2];
	return *this;
}
// *= med t
inline vctr& vctr::operator*=(const float t) {
	e[0] *= t;
	e[1] *= t;
	e[2] *= t;
	return *this;
}
// /= med t
inline vctr& vctr::operator/=(const float t) {
	float k = 1.0f / t;

	e[0] *= k;
	e[1] *= k;
	e[2] *= k;
	return *this;
}
// enhedsvektor
inline vctr e_vektor(vctr v) {
	return v / v.laengde();
}

#endif