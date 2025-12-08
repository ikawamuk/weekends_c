#include "util.h"

double random_double(double min, double max)
{
	return min + (max - min) * (rand() / (RAND_MAX + 1.0));
}

double clamp(double x, double min, double max)
{
	if (x < min)
		return min;
	if (x > max)
		return max;
	return (x);
}
