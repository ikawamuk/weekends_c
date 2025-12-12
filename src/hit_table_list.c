#include "hit_table_list.h"
#include "t_range.h"
#include "define.h"
#include "aabb.h"
#include "bvh.h"

t_hit_table_list	construct_htl(void)
{
	t_hit_table_list	list;

	list.hit_table.hit = hit_htl;
	list.hit_table.bounding_box = bounding_htl;
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

bool	hit_htl(const void *s, const t_ray ray, t_hit_record *rec, t_t_range *t_range)
{
	const t_hit_table_list	*self = s;
	t_hit_table_node	*tail_p = self->head;
	t_hit_record		temp_rec;
	t_t_range			temp_range = construct_t_range(HIT_T_MIN, INFINITY);
	bool				hit_anything = false;

	(void)(t_range);
	while (tail_p)
	{
		if (!tail_p->data) // 無限ループの可能性ある?
			continue ;
		if (tail_p->data->hit(tail_p->data, ray, &temp_rec, &temp_range)
		&& check_range(temp_rec.t, temp_range))
		{
			hit_anything = true;
			*rec = temp_rec;
		}
		tail_p = tail_p->next;
	}
	return (hit_anything);
}

bool	bounding_htl(const void *s, t_t_range t_range, t_aabb *outbox)
{
	const t_hit_table_list	*self = (const t_hit_table_list *)s;
	t_hit_table_node		*curr;
	t_aabb					temp_box;
	bool					first_box = true;

	if (self == NULL || self->head == NULL)
		return (false);
	while (curr)
	{
		if (!curr->data->bounding_box(curr->data, t_range, &temp_box))// 難しい。引数をどうしようか迷う。
			return (false);
		if (first_box)
			*outbox = temp_box;
		else
			*outbox = surrounding_box(*outbox, temp_box);
		first_box = false;
		curr = curr->next;
	}
	return (true);
}