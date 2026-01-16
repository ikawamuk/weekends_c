#ifndef PLANE_H
# define PLANE_H

# include "hit_table.h"
# include "vec3.h"

typedef struct s_plane {
	t_hit_table	hit_table;
	t_vec3		normal;
	t_point3	point;
}	t_plane;

t_plane	*gen_plane(const t_point3 p, const t_vec3 _normal, void *mat_ptr, void *texture_p);

#endif