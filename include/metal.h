#ifndef METAL_H
# define METAL_H

#include "material.h"

/*
@fuzz ザラザラ具合*/
typedef struct s_metal
{
	t_material	material;
	double		fuzz;
}	t_metal;

t_metal	*gen_metal(double fuzz);

#endif