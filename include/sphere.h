#ifndef SPHERE_H
#define SPHERE_H

#include <stdlib.h>
#include "hit_table.h"
#include "vec3.h"
#include "material.h"

typedef struct s_sphere
{
	t_hit_table	hit_table;
	t_point3	center;
	double		radius;
}	t_sphere;

t_sphere	construct_sphere(const t_point3 cen, const double r, void *mat_ptr);
t_sphere	*gen_sphere(const t_point3 cen, const double r, void *mat_ptr);

#endif
