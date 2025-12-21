#ifndef BVH_H
# define BVH_H

# include "bvh_info.h"
# include "hit_node.h"
# include "ray.h"
# include "range.h"
# include <stddef.h>

t_hit_node	*gen_bvh(t_bvh_info *objects, size_t start, size_t end);

#endif