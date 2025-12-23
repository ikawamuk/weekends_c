#ifndef BVH_H
# define BVH_H

# include "hit_table_array.h"
# include "hit_node.h"
# include "ray.h"
# include "range.h"
# include <stddef.h>

t_hit_table	*gen_bvh(t_hit_table_array *objects, size_t start, size_t end);
void		clear_bvh(t_hit_table *self);

#endif