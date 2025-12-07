#ifndef LAMBERTIAN_H
# define LAMBERTIAN_H

#include "material.h"

typedef struct s_lambertian
{
	t_material	material;
	t_color		albedo;
}	t_lambertian;

t_lambertian	construct_lambertian(t_color alb);
bool			scatter_lambertian(void *s, t_hit_record rec, t_color *attenuation, t_ray *scattered);
t_lambertian	*gen_lambertian(t_color alb);

#endif
