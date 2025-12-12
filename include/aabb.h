#ifndef AABB_H
# define AABB_H

# include "vec3.h"
# include "bvh.h"

typedef struct s_aabb {
	t_hit_table	hit_table;
	t_point3	min;
	t_point3	max;
}	t_aabb;

t_aabb	construct_aabb(const t_point3 _min, const t_point3 _max);
t_aabb	*gen_aabb(const t_point3 _min, const t_point3 _max);

// box.c
t_aabb	surrounding_box(t_aabb box0, t_aabb box1);

#endif