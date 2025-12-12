#ifndef RT_UTILS_H
# define RT_UTILS_H

#include <math.h>
#include <stdlib.h>
#include "define.h"

double	random_double(double min, double max);
int		random_int(int min, int max);
double	clamp(double x, double min, double max);

#endif
