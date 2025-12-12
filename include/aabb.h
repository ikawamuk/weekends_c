#ifndef AABB_H
# define AABB_H

# include "vec3.h"
# include "t_range.h"
# include "ray.h"
# include <stdbool.h>

typedef struct s_aabb {
	t_point3	min;
	t_point3	max;
	bool		(*hit)(const void*, const t_ray ray, t_t_range t_range);
}	t_aabb;

t_aabb	construct_aabb(const t_point3 _min, const t_point3 _max);
t_aabb	*gen_aabb(const t_point3 _min, const t_point3 _max);

// box.c
t_aabb	surrounding_box(t_aabb box0, t_aabb box1);

#endif