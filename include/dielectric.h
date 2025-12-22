#ifndef DIELECTRIC_H
# define DIELECTRIC_H

#include "material.h"

typedef struct s_dielectric
{
	t_material	material;
	double		refract_idx;
}	t_dielectric;

t_dielectric	*gen_dielectric(double refract_idx);

#endif
