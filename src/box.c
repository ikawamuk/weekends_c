#include "aabb.h"
#include "hit_table.h"
#include <stdio.h>

t_aabb	surrounding_box(t_aabb box0, t_aabb box1)
{
	t_point3	small = construct_vec(fmin(box0.min.x, box1.min.x), \
									fmin(box0.min.y, box1.min.y), \
									fmin(box0.min.z, box1.min.z));
	t_point3	big = construct_vec(fmax(box0.max.x, box1.max.x), \
									fmax(box0.max.y, box1.max.y), \
									fmax(box0.max.z, box1.max.z));
	return (construct_aabb(small, big));
}

bool	box_compare(const t_hit_table a, const t_hit_table b, int axis)
{
	t_aabb	a_box;
	t_aabb	b_box;

	if (!a.bounding_box(&a, &a_box) \
	|| !b.bounding_box(&b, &b_box))
		fprintf(stderr, "No bounding box in bvh node constructor.\n");
	return (axis_vec(a_box.min, axis) < axis_vec(b_box.min, axis));
}

bool	box_x_compare(const t_hit_table a, const t_hit_table b)
{
	return (box_compare(a, b, 0));
}

bool	box_y_compare(const t_hit_table a, const t_hit_table b)
{
	return (box_compare(a, b, 1));
}

bool	box_z_compare(const t_hit_table a, const t_hit_table b)
{
	return (box_compare(a, b, 2));
}
