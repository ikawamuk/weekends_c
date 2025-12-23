#include "aabb.h"
#include <stddef.h>
#include <math.h>

#include <stdlib.h>
static void	swap_double(double *a, double *b);
static bool	hit_aabb(const t_aabb *self, t_ray ray, t_range range);

t_aabb	construct_aabb(t_point3 _min, t_point3 _max)
{
	t_aabb	aabb;

	aabb.min = _min;
	aabb.max = _max;
	// 重心は比較にしか使われないので0.5はかけない
	aabb.centroid = add_vec(_min, _max);
	aabb.hit = hit_aabb;
	return (aabb);
}

/*
@brief 2つの直方体を囲む直方体
*/
t_aabb	surrounding_box(t_aabb box0, t_aabb box1)
{
	t_point3	_small;
	t_point3	_big;

	_small = construct_vec(fmin(box0.min.x, box1.min.x), \
						fmin(box0.min.y, box1.min.y), \
						fmin(box0.min.z, box1.min.z));
	_big = construct_vec(fmax(box0.max.x, box1.max.x), \
						fmax(box0.max.y, box1.max.y), \
						fmax(box0.max.z, box1.max.z));
	return (construct_aabb(_small, _big));
}

static void	swap_double(double *a, double *b)
{
	double	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

static bool	hit_aabb(const t_aabb *self, t_ray ray, t_range range)
{
	size_t	i;
	t_range	tmp;
	double	inv_d;

	i = 0;
	while (i < 3)
	{
		inv_d = 1 / axis_vec(ray.direct, i);
		tmp.min = (axis_vec(self->min, i) - axis_vec(ray.origin, i)) * inv_d;
		tmp.max = (axis_vec(self->max, i) - axis_vec(ray.origin, i)) * inv_d;
		if (inv_d < 0.0f)
			swap_double(&tmp.min, &tmp.max);
		range.min = fmax(tmp.min, range.min);
		range.max = fmin(tmp.max, range.max);
		if (range.max <= range.min)
			return (false);
		i++;
	}
	return (true);
}
