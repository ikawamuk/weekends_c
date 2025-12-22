#ifndef UTIL_H
# define UTIL_H

#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include "define.h"
#include "vec3.h"

double	random_double(double min, double max);
int		random_int(int min, int max);
double	clamp(double x, double min, double max);
void	get_sphere_uv(t_vec3 p, double *u, double *v);

#endif
