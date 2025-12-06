#include "hit_table_list.h"

t_hit_table_list	construct_htl(void)
{
	t_hit_table_list	list;

	list.hit_table.hit = hit_htl;
	list.head = NULL;
	return (list);
}

bool	add_htl(t_hit_table_list *list_p, void *d)
{
	t_hit_table *data = d;
	t_hit_table_node *node_p;
	t_hit_table_node *tail_p;

	if (!list_p)
		return (true);
	node_p = malloc(sizeof(*node_p));
	if (!node_p)
		return false;
	node_p->data = data;
	node_p->next = NULL;
	if (list_p->head == NULL)
	{
		list_p->head = node_p;
		return true;
	}
	tail_p = list_p->head;
	while (tail_p->next)
		tail_p = tail_p->next;
	tail_p->next = node_p;
	return (true);
}

void	clear_htl(t_hit_table_list list)
{
	t_hit_table_node	*cur;

	while (list.head)
	{
		cur = list.head;
		list.head = list.head->next;
		free(cur->data->mat_ptr);
		free(cur->data);
		free(cur);
	}
	return ;
}

bool	hit_htl(void *s, const t_ray ray, t_hit_record *rec)
{
	t_hit_table_list	*self = s;
	t_hit_table_node	*tail_p = self->head;
	t_hit_record		temp_rec;
	bool				hit_anything = false;
	double				closest_so_far = INFINITY;

	while (tail_p)
	{
		if (!tail_p->data)
			continue ;
		if (tail_p->data->hit(tail_p->data, ray, &temp_rec)
		&& temp_rec.t < closest_so_far)
		{
			hit_anything = true;
			closest_so_far = temp_rec.t;
			*rec = temp_rec;
		}
		tail_p = tail_p->next;
	}
	return (hit_anything);
}
