#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include <stdbool.h>
#include <stdlib.h>
#include "hit_table.h"
#include "t_range.h"

typedef struct s_hit_table_node t_hit_table_node;

struct s_hit_table_node
{
	t_hit_table			*data;
	t_hit_table_node	*next;
};

typedef struct s_hit_table_list
{
	t_hit_table			hit_table;
	t_hit_table_node	*head;
}	t_hit_table_list;

t_hit_table_list	construct_htl(void);
bool				add_htl(t_hit_table_list *list_p, void *d);
void				clear_htl(t_hit_table_list list);
bool				hit_htl(const void *s, const t_ray ray, t_hit_record *rec, t_t_range t_range);

#endif
