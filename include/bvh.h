#ifndef BVH_H
# define BVH_H

# include "hit_node.h"
# include "ray.h"
# include "range.h"
# include <stddef.h>

t_hit_table	*gen_bvh(t_hit_table **hit_table_array, size_t start, size_t end);
t_hit_table	construct_bvh_htl(const t_hit_node *node);
void		clear_bvh(t_hit_table *self);

#endif