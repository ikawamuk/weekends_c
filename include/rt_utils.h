#ifndef RT_UTILS_H
# define RT_UTILS_H

#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include "define.h"
#include "vec3.h"

double	random_double(double min, double max);
int		random_int(int min, int max);
double	clamp(double x, double min, double max);

#endif
