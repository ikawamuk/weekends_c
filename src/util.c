#include <stdint.h>
#include "util.h"

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

int	random_int(int min, int max)
{
	if (min > max)
		return (min);
	int	range = max - min + 1;
	return (min + (int)(random_double(0.0, 1.0) * range));
}

double clamp(double x, double min, double max)
{
	if (x < min)
		return min;
	if (x > max)
		return max;
	return (x);
}
