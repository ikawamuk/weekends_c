#ifndef HIT_NODE_H
# define HIT_NODE_H

# include "hit_table.h"
# include <stddef.h>

typedef struct s_hit_node t_hit_node;

/*
@brief 木構造でオブジェクト情報を格納
*/
struct s_hit_node
{
	t_hit_table		hit_table;
	t_hit_table		*lhs;
	t_hit_table		*rhs;
};

#endif