#ifndef LIGHT_H
# define LIGHT_H

#include "material.h"

typedef struct s_ight
{
	t_material	material;
	t_color		emit_color;
}	t_light;

t_light	construct_light(t_color emit);
bool	scatter_light(void*, t_hit_record, t_color*, t_ray*);
t_color	emitted_light(void *s, t_hit_record rec);
t_light	*gen_light(t_color emit);

#endif
