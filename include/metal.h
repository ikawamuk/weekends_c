#ifndef METAL_H
# define METAL_H

#include "material.h"

typedef struct s_metal
{
	t_material	material;
	t_color		albedo;
	double		fuzz;
}	t_metal;

t_metal	*gen_metal(t_color alb, double fuzz);

#endif