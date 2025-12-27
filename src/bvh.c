#include "bvh.h"
#include "hit_node.h"
#include "rt_utils.h"
#include "libft.h"
#include <stddef.h>
#include <stdio.h>

typedef bool (*comp)(const t_hit_table *, const t_hit_table *);

static t_hit_node	construct_bvh(t_hit_table **hit_table_array, size_t start, comp comparator);
static comp			get_random_comp(void);
static bool			box_x_compare(const t_hit_table *a, const t_hit_table *b);
static bool			box_y_compare(const t_hit_table *a, const t_hit_table *b);
static bool			box_z_compare(const t_hit_table *a, const t_hit_table *b);
static bool			hit_bvh(const void *s, const t_ray ray, t_hit_record *rec, t_range range);
static void			sort_hit_table_array(t_hit_table **hit_table_array, int start, int end, comp comparator);

/*
@brief BVH構造を作成する関数
*/
t_hit_table	*gen_bvh(t_hit_table **hit_table_array, size_t start, size_t end)
{
	t_hit_node	*node;
	size_t		object_span = end - start;
	comp		comparator;

	if (object_span == 0)
		return (hit_table_array[start]);
	node = ft_calloc(1, sizeof(t_hit_node));
	if (!node)
		return (NULL);
	comparator = get_random_comp();
	if (object_span == 1)
		*node = construct_bvh(hit_table_array, start, comparator);
	else
	{
		sort_hit_table_array(hit_table_array, start, end, comparator);
		size_t	mid = start + (object_span) / 2;
		node->lhs = gen_bvh(hit_table_array, start, mid);
		node->rhs = gen_bvh(hit_table_array, mid + 1, end);
	}
	node->hit_table = construct_bvh_htl(node);
	return ((t_hit_table *)node);
}

static t_hit_node	construct_bvh(t_hit_table **hit_table_array, size_t start, comp comparator)
{
	t_hit_node	node;

	if (comparator(hit_table_array[start], hit_table_array[start + 1]))
	{
		node.lhs = hit_table_array[start];
		node.rhs = hit_table_array[start + 1];
	}
	else
	{
		node.lhs = hit_table_array[start + 1];
		node.rhs = hit_table_array[start];
	}
	return (node);
}

t_hit_table	construct_bvh_htl(const t_hit_node *node)
{
	t_hit_table	htl;

	ft_bzero(&htl, sizeof(t_hit_table));
	htl.aabb = surrounding_box(node->lhs->aabb, node->rhs->aabb);
	// 下部のノードがどちらも平面の場合のみaabbを持たない。
	if (node->lhs->have_aabb && node->rhs->have_aabb)
		htl.have_aabb = true;
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

static bool	box_compare(const t_hit_table *a, const t_hit_table *b, int axis)
{
	if (!a->have_aabb || !b->have_aabb)
		return (false);
	return (axis_vec(a->aabb.centroid, axis) <  axis_vec(b->aabb.centroid, axis));
}

static bool	box_x_compare(const t_hit_table *a, const t_hit_table *b)
{
	return (box_compare(a, b, 0));
}

static bool	box_y_compare(const t_hit_table *a, const t_hit_table *b)
{
	return (box_compare(a, b, 1));
}

static bool	box_z_compare(const t_hit_table *a, const t_hit_table *b)
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
	if (self->hit_table.have_aabb \
		&& self->hit_table.aabb.hit(&self->hit_table.aabb, ray, range) == false)
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

	if (!self)
		return ;
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

static void	swap_info(t_hit_table **a, t_hit_table **b)
{
	t_hit_table	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

/*
@brief t_hit_table*の配列をクイックソート
*/
static void	sort_hit_table_array(t_hit_table **hit_table_array, int start, int end, comp comparator)
{
	int			left;
	int			right;
	t_hit_table	**pivot;

	if (end <= start)
		return ;
	if (start + 1 == end)
	{
		if (comparator(hit_table_array[end], hit_table_array[start]))
			swap_info(&hit_table_array[start], &hit_table_array[end]);
		return ;
	}
	left = start;
	right = (end - 1);
	pivot = &hit_table_array[end];
	while (left < right)
	{
		while (left < end && comparator(hit_table_array[left], *pivot))
			left++;
		while (start < right && comparator(*pivot, hit_table_array[right]))
			right--;
		if (right <= left)
			break ;	
		swap_info(&hit_table_array[left++], &hit_table_array[right--]);
	}
	swap_info(&hit_table_array[left], pivot);
	sort_hit_table_array(hit_table_array, start, left - 1, comparator);
	sort_hit_table_array(hit_table_array, left + 1, end, comparator);
}
