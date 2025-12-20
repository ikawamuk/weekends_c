#include "hit_node.h"
#include "bvh_info.h"
#include "rt_utils.h"
#include "libft.h"
#include <stddef.h>

#include <stdio.h>

static t_hit_node	*add_new_node(t_bvh_info *object);
static bool			box_x_compare(const t_bvh_info *a, const t_bvh_info *b);
static bool			box_y_compare(const t_bvh_info *a, const t_bvh_info *b);
static bool			box_z_compare(const t_bvh_info *a, const t_bvh_info *b);

t_hit_table	*construct_bvh(t_bvh_info *objects, size_t start, size_t end)
{
	int			axis = 0/* random_int(0, 2) */;
	bool		(*comparator)(const t_bvh_info *, const t_bvh_info *);
	t_hit_node	*node;

	size_t	object_span = end - start;
	if (object_span == 0)
		return (objects[start].data);
	node = calloc(1, sizeof(t_bvh_info));
	if (!node)
		return (NULL);
	if (axis == 0)
		comparator = box_x_compare;
	else if (axis == 1)
		comparator = box_y_compare;
	else
		comparator = box_z_compare;
	if (object_span == 1) {
		if (comparator(&objects[start], &objects[start+1])) {
			node->lhs = objects[start].data;
			node->rhs = objects[start + 1].data;
		} else {
			node->lhs = objects[start + 1].data;
			node->rhs = objects[start].data;
		}
	} else {
		sort_bvh_info(objects, start, end, comparator);
		size_t	mid = start + (object_span) / 2;
		node->lhs = construct_bvh(objects, start, mid);
		node->rhs = construct_bvh(objects, mid, end);
	}
	node->box = surrounding_box(node->hit_table.aabb, node->hit_table.aabb);
	return (node);
}

static t_hit_node	*add_new_node(t_bvh_info *object)
{
	t_hit_node	*node;

	node = ft_calloc(1, sizeof(t_hit_node));
	if (!node)
		return (NULL);
	node->data = object->data;
	if (object->have_aabb)
		node->box = object->aabb;
	return (node);
}

static bool	box_compare(const t_bvh_info *a, const t_bvh_info *b, int axis)
{
	if (!a->have_aabb || !b->have_aabb)
		return (false);
	return (axis_vec(a->centroid, axis) <  axis_vec(b->centroid, axis));
}

static bool	box_x_compare(const t_bvh_info *a, const t_bvh_info *b)
{
	return (box_compare(a, b, 0));
}

static bool	box_y_compare(const t_bvh_info *a, const t_bvh_info *b)
{
	return (box_compare(a, b, 1));
}

static bool	box_z_compare(const t_bvh_info *a, const t_bvh_info *b)
{
	return (box_compare(a, b, 2));
}

/*
@brief bvh木構造をレイとの交差判定を行う
*/
bool	hit_bvh(const t_hit_node *self, t_ray ray, t_hit_record *rec, t_range range)
{
	bool	hit_left;
	bool	hit_right;

	if (self == NULL)
		return (false);
	// まずboxにヒットしないものをfalseとする
	if (self->box.hit(&self->box, ray, range) == false)
		return (false);
	// dataがある時はそれがノードではなく葉であることを示す
	if (self->data)
		return (self->data->hit(self->data, ray, rec, range));
	hit_left = hit_bvh(self->lhs, ray, rec, range);
	if (hit_left)
		range.max = rec->t;
	hit_right = hit_bvh(self->rhs, ray, rec, range);
	return (hit_left || hit_right);
}
