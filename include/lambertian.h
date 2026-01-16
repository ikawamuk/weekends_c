#ifndef LAMBERTIAN_H
# define LAMBERTIAN_H

#include "material.h"
#include "texture.h"

typedef struct s_lambertian
{
	t_material	material;
}	t_lambertian;

t_lambertian	construct_lambertian(void);
bool			scatter_lambertian(void *s, t_hit_record *rec, t_scatter_record *srec);
double			lambertian_pdf(void *s, t_hit_record rec, t_ray scattered);
t_lambertian	*gen_lambertian(void);

#endif
