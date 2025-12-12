#ifndef BOX_H
# define BOX_H

# include "hit_table_list.h"

bool	box_compare(const t_hit_table a, const t_hit_table b, int axis);
bool	box_x_compare(const t_hit_table a, const t_hit_table b);
bool	box_y_compare(const t_hit_table a, const t_hit_table b);
bool	box_z_compare(const t_hit_table a, const t_hit_table b);

#endif