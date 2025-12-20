#ifndef AABB_H
# define AABB_H

# include "aabb.h"
# include "ray.h"
# include "range.h"
# include <stdbool.h>

typedef struct s_aabb t_aabb;

/*
@brief 包含直方体を表す構造体
@param min 原点に最も近い点
@param max 原点から最も遠い点
*/
struct s_aabb
{
	t_point3	min;
	t_point3	max;
	bool		(*hit)(const t_aabb *, t_ray, t_range);
};

t_aabb	construct_aabb(t_point3 _min, t_point3 _max);
t_aabb	surrounding_box(t_aabb box0, t_aabb box1);

#endif