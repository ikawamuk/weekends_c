#ifndef HIT_TABLE_ARRAY_H
# define HIT_TABLE_ARRAY_H

# include "hit_table.h"
# include "vec3.h"
# include "aabb.h"
# include <stddef.h>

/*
@brief bvhを構築するための準備構造体
@brief ポインタのみ保持する
*/
typedef struct s_hit_table_array
{
	t_hit_table	*data;
}	t_hit_table_array;

t_hit_table_array	construct_hit_table_array(char *line);
void		sort_hit_table_array(t_hit_table_array *info, int start, int end, bool (*comparator)(const t_hit_table_array *, const t_hit_table_array *));

#endif