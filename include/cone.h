#ifndef CONE_H
# define CONE_H

# include "hit_table.h"
# include "vec3.h"

typedef struct s_cone
{
	t_hit_table	hit_table;
	t_vec3		direct;
	double		half_angle; // radian
	t_point3	center;
}	t_cone;

t_cone	*gen_cone(t_point3 _center, t_vec3 _direct, double half_angle, void *mat_ptr);

#endif