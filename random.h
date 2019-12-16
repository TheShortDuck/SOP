#ifndef RANDOMH
#define RANDOMH

#include <random>

inline double rand_double() {
	std::random_device rd;
	std::mt19937 _rng_generator(rd());
	return std::generate_canonical<double, std::numeric_limits<double>::digits>(_rng_generator);
}

#endif
