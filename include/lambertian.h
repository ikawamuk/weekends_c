#ifndef LAMBERTIAN_H
# define LAMBERTIAN_H

#include "material.h"

typedef struct s_lambertian
{
	t_material	mat;
	t_color		albedo;
}	t_lambertian;

t_lambertian	construct_lambertian(t_color alb);

t_lambertian	*gen_lambertian(t_color alb);

#endif
