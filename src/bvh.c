#include "bvh.h"
#include "world.h"
#include "rt_utils.h"

bool	hit_bvh(const void *s, const t_ray ray, t_hit_record *rec, t_t_range *t_range)
{
	const t_bvh_node	*self = (const t_bvh_node *)s;
	bool	hit_left;
	bool	hit_right;

	hit_left = hit_bvh(self->left, ray, rec, t_range);
	hit_right = hit_bvh(self->right, ray, rec, t_range);
	return (hit_left || hit_right);
}

t_bvh_node	construct_bvh_node(t_hit_table_list *world, size_t start, size_t end, t_t_range t_range)
{
	int		axis = random_int(0, 2);
	double	comparator;

	comparator = 
}
