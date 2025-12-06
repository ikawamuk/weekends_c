#ifndef METAL_H
# define METAL_H

#include "material.h"

typedef struct s_metal
{
	t_material	mat;
	t_color		albedo;
}	t_metal;

t_metal	construct_metal(t_color alb);

t_metal	*gen_metal(t_color alb);

#endif