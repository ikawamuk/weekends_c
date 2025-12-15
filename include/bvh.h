#ifndef BVH_H
# define BVH_H

# include "vec3.h"
# include "hit_table_list.h"
# include "hit_table.h"
# include "aabb.h"

typedef struct s_bvh_node t_bvh_node;
// left, rightには球等の通常オブジェクト
// も含まれるため、t_hit_table
struct s_bvh_node
{
	t_hit_table	hit_table;
	t_bvh_node	*left;
	t_bvh_node	*right;
	t_aabb		box;
};

t_bvh_node	*construct_bvh_node(t_hit_table_list *htl, size_t start, size_t end);

#endif