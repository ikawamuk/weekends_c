#ifndef MATERIAL_H
# define MATERIAL_H

#include "hit_table.h"
#include "vec3.h"
#include "ray.h"

typedef struct s_material
{
	bool	(*scatter)(void *self, t_hit_record rec, t_color *attenuation, t_ray *scatterd);
}	t_material;

#endif
