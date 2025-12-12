#ifndef BVH_H
# define BVH_H

# include "vec3.h"
# include "hit_table.h"
# include "aabb.h"

typedef struct s_bvh_node t_bvh_node;

typedef struct s_bvh_node
{
	t_bvh_node	*left;
	t_bvh_node	*right;
	t_aabb		box;
};

#endif