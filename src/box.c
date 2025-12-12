#include "aabb.h"

t_aabb	surrounding_box(t_aabb box0, t_aabb box1)
{
	t_point3	small = construct_vec(fmin(box0.min.x, box1.min.x), \
									fmin(box0.min.y, box1.min.y), \
									fmin(box0.min.z, box1.min.z));
	t_point3	big = construct_vec(fmax(box0.max.x, box1.max.x), \
									fmax(box0.max.x, box1.max.x), \
									fmax(box0.max.x, box1.max.z));
	return (construct_aabb(small, big));
}

static bool	box_compare(const )