#ifndef LIGHT_H
# define LIGHT_H

#include "material.h"

typedef struct s_ight
{
	t_material	material;
	t_color		emit_color;
}	t_light;

t_light	construct_light(t_color emit);
bool	scatter_light(void* s, t_hit_record *rec, t_scatter_record *srec);
t_color	emitted_light(void *s, t_hit_record rec);
double	light_pdf(void *self, t_hit_record rec, t_ray scattered);
t_light	*gen_light(t_color emit);

#endif
