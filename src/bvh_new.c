#include "hit_table.h"
#include "hit_node.h"
#include <stddef.h>
#include <float.h>

# define COST_UNIT 1

t_hit_table	*nodes[10000];

/*
@param is_leaf 葉の判定
@param index 配列の先頭インデックス
@param size 保持するポリゴンの数
*/
// typedef struct	bvh_node {
// 	t_hit_table	hit_table;
// 	bool		is_leaf;
// 	size_t		index;
// 	size_t		size;
// }	t_bvh_node;

typedef bool	(*comp)(const t_hit_table *, const t_hit_table *);
static bool		box_compare(const t_hit_table *a, const t_hit_table *b, int axis);
static void		sort_hit_table_array(t_hit_table **hit_table_array, int start, int end, int axis);
static void		swap_info(t_hit_table **a, t_hit_table **b);
t_hit_table		*gen_hit_node(t_hit_table *lhs, t_hit_table *rhs);

int		used_node_count = 0;
float	T_tri = 1.0f;
float	T_aabb = 1.0f;

// void	makeLeaf(t_hit_table **objs, t_hit_node *node) {
// 	node->lhs = NULL;
// 	node->rhs = NULL;
// 	node = objs;
// }

t_aabb	create_bounding_aabb(t_hit_table **objs, size_t objs_size)
{
	size_t	i = 0;
	t_aabb	aabb;

	aabb = empty_aabb();
	while (i < objs_size)
		aabb = surrounding_box(aabb, objs[i++]->aabb);
	return (aabb);
}

t_hit_table	*gen_bvh(t_hit_table **objs, size_t start, size_t end)
{
	t_aabb	bounding_all;
	size_t	objs_size = end - start + 1;
	static int	depth = 0;

	if (objs_size == 1)
		return (objs[start]);
	if (objs_size == 2)
		return (gen_hit_node(objs[start], objs[start + 1]));
	bounding_all = create_bounding_aabb(objs, objs_size);
	float	bestCost = INFINITY;

	int		bestAxis = 0;
	size_t	bestSplitIndex = start;
	float	SA_root = surface_area(bounding_all);
	t_aabb	*SA_1 = ft_calloc(objs_size, sizeof(t_aabb));
	t_aabb	*SA_2 = ft_calloc(objs_size, sizeof(t_aabb));
	for (int axis = 0; axis < 3; axis++)
	{
		sort_hit_table_array(objs, start, end, axis);
		ft_bzero(SA_1, sizeof(t_aabb) * (objs_size));
		ft_bzero(SA_2, sizeof(t_aabb) * (objs_size));
		SA_1[0] = objs[start]->aabb;
		for (size_t i = 1; i < objs_size; i++)
			SA_1[i] = surrounding_box(SA_1[i - 1], objs[i + start]->aabb);
		SA_2[objs_size - 1] = objs[end]->aabb;
		for (size_t i = objs_size - 2; i != SIZE_MAX; i--)
			SA_2[i] = surrounding_box(SA_2[i + 1], objs[i + start]->aabb);
		for (size_t i = 0; i < objs_size - 1; i++) {
			float	cost = 2*T_aabb + \
(surface_area(SA_1[i]) * (i + 1) + (surface_area(SA_2[i + 1])) \
* (objs_size - (i + 1))) * T_tri / SA_root;
			if (cost < bestCost) {
				bestCost = cost;
				bestAxis = axis;
				bestSplitIndex = i + start;
			}
		}
	}
	free(SA_1);
	free(SA_2);
	sort_hit_table_array(objs, start, end, bestAxis);
	return (gen_hit_node(gen_bvh(objs, start, bestSplitIndex), \
gen_bvh(objs, bestSplitIndex + 1, end)));
}

static bool	box_compare(const t_hit_table *a, const t_hit_table *b, int axis)
{
	if (!a->have_aabb || !b->have_aabb)
		return (false);
	return (axis_vec(a->aabb.centroid, axis) <  axis_vec(b->aabb.centroid, axis));
}

static void	sort_hit_table_array(t_hit_table **hit_table_array, int start, int end, int axis)
{
	int			left;
	int			right;
	t_hit_table	**pivot;

	if (end <= start)
		return ;
	if (start + 1 == end)
	{
		if (box_compare(hit_table_array[end], hit_table_array[start], axis))
			swap_info(&hit_table_array[start], &hit_table_array[end]);
		return ;
	}
	left = start;
	right = (end - 1);
	pivot = &hit_table_array[end];
	while (left < right)
	{
		while (left < end && box_compare(hit_table_array[left], *pivot, axis))
			left++;
		while (start < right && box_compare(*pivot, hit_table_array[right], axis))
			right--;
		if (right <= left)
			break ;	
		swap_info(&hit_table_array[left++], &hit_table_array[right--]);
	}
	swap_info(&hit_table_array[left], pivot);
	sort_hit_table_array(hit_table_array, start, left - 1, axis);
	sort_hit_table_array(hit_table_array, left + 1, end, axis);
}

static void	swap_info(t_hit_table **a, t_hit_table **b)
{
	t_hit_table	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}
