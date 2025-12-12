#include <stdint.h>
#include "rt_utils.h"

static uint64_t	random_uint64(void)
{
	static uint64_t x = 0x629d97afad9281f2; // /bin/bash -c openssl rand -hex 8
	x ^= x << 12;
	x ^= x >> 25;
	x ^= x << 27;
	return (x);
}

double random_double(double min, double max)
{
	uint64_t u = random_uint64() >> 11;
	double v = (double)u * (1.0 / 9007199254740992.0);
	return (min + (max - min) * v);
}

// minからmaxのランダムなint
// bvhで利用
int	random_int(int min, int max)
{
	return (min + (int)random_uint64() % (max - min + 1));
}

double clamp(double x, double min, double max)
{
	if (x < min)
		return min;
	if (x > max)
		return max;
	return (x);
}
