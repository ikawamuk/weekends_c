#include "bvh.h"
#include "hit_node.h"
#include "bvh_info.h"
#include "rt_utils.h"
#include "libft.h"
#include <stddef.h>
#include <stdio.h>

typedef bool (*comp)(const t_bvh_info *, const t_bvh_info *);

// static t_hit_node	*add_new_node(t_bvh_info *object);
t_hit_node			construct_bvh(t_bvh_info *bvh_info_array, size_t start, comp comparator);
static t_hit_table	construct_bvh_htl(const t_hit_node *node);
static comp			get_random_comp(void);
static bool			box_x_compare(const t_bvh_info *a, const t_bvh_info *b);
static bool			box_y_compare(const t_bvh_info *a, const t_bvh_info *b);
static bool			box_z_compare(const t_bvh_info *a, const t_bvh_info *b);
static bool			hit_bvh(const void *s, const t_ray ray, t_hit_record *rec, t_range range);

t_hit_table	*gen_bvh(t_bvh_info *bvh_info_array, size_t start, size_t end)
{
	t_hit_node	*node;
	size_t		object_span = end - start;
	comp		comparator;

	if (object_span == 0)
		return (bvh_info_array->data);
	node = ft_calloc(1, sizeof(t_hit_node));
	if (!node)
		return (NULL);
	comparator = get_random_comp();
	if (object_span == 1)
		*node = construct_bvh(bvh_info_array, start, comparator);
	else
	{
		sort_bvh_info(bvh_info_array, start, end, comparator);
		size_t	mid = start + (object_span) / 2;
		node->lhs = gen_bvh(bvh_info_array, start, mid);
		node->rhs = gen_bvh(bvh_info_array, mid, end);
	}
	node->hit_table = construct_bvh_htl(node);
	return ((t_hit_table *)node);
}

t_hit_node	construct_bvh(t_bvh_info *bvh_info_array, size_t start, comp comparator)
{
	t_hit_node	node;

	if (comparator(&bvh_info_array[start], &bvh_info_array[start + 1]))
	{
		node.lhs = bvh_info_array[start].data;
		node.rhs = bvh_info_array[start + 1].data;
	}
	else
	{
		node.lhs = bvh_info_array[start + 1].data;
		node.rhs = bvh_info_array[start].data;
	}
	return (node);
}

static t_hit_table	construct_bvh_htl(const t_hit_node *node)
{
	t_hit_table	htl;

	htl.aabb = surrounding_box(node->lhs->aabb, node->rhs->aabb);
	htl.hit = hit_bvh;
	htl.clear = clear_bvh;
	return (htl);
}

/*
@brief ランダムに選ばれた軸を下にした比較関数を生成する
*/
static comp	get_random_comp(void)
{
	int	axis;

	axis = random_int(0, 2);
	if (axis == 0)
		return (box_x_compare);
	else if (axis == 1)
		return (box_y_compare);
	return (box_z_compare);
}

static bool	box_compare(const t_bvh_info *a, const t_bvh_info *b, int axis)
{
	if (!a->data->have_aabb || !b->data->have_aabb)
		return (false);
	return (axis_vec(a->data->aabb.centroid, axis) <  axis_vec(b->data->aabb.centroid, axis));
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
static bool	hit_bvh(const void *s, const t_ray ray, t_hit_record *rec, t_range range)
{
	const t_hit_node	*self;
	bool	hit_left;
	bool	hit_right;

	self = (const t_hit_node *)s;
	if (self == NULL)
		return (false);
	// まずboxにヒットしないものをfalseとする
	if (self->hit_table.aabb.hit(&self->hit_table.aabb, ray, range) == false)
		return (false);
	hit_left = self->lhs->hit(self->lhs, ray, rec, range);
	// 左側に当たった時はrangeを更新
	if (hit_left)
		range.max = rec->t;
	hit_right = self->rhs->hit(self->rhs, ray, rec, range);
	return (hit_left || hit_right);
}

void	clear_bvh(t_hit_table *self)
{
	t_hit_node	*node;

	node = (t_hit_node *)self;
	if (node->lhs)
	{
		node->lhs->clear(node->lhs);
		node->lhs = NULL;
	}
	if (node->rhs)
	{
		node->rhs->clear(node->rhs);
		node->rhs = NULL;
	}
	free(node);
}
