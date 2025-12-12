#ifndef BVH_H
# define BVH_H

# include "vec3.h"
# include "hit_table_list.h"
# include "hit_table.h"
# include "aabb.h"

// left, rightには球等の通常オブジェクト
// も含まれるため、t_hit_table
typedef struct s_bvh_node
{
	t_hit_table	hit_table;
	t_hit_table	*left;
	t_hit_table	*right;
	t_aabb		box;
}	t_bvh_node;

#endif