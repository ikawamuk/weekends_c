#include "bvh.h"
#include "world.h"
#include "rt_utils.h"
#include "box.h"
#include <stdio.h>

bool	hit_bvh(const void *s, const t_ray ray, t_hit_record *rec, t_t_range t_range)
{
	const t_bvh_node	*self = (const t_bvh_node *)s;
	bool	hit_left;
	bool	hit_right;

	if (!self->box.hit(&self->box, ray, t_range))
		return (false);
	hit_left = self->left->hit_table.hit(self->left, ray, rec, t_range);
	if (hit_left)
		t_range.max = rec->t;
	hit_right = self->right->hit_table.hit(self->right, ray, rec, t_range);
	return (hit_left || hit_right);
}

bool	bounding_bvh(const void *s, t_aabb *output_box)
{
	const t_bvh_node	*self = (const t_bvh_node *)s;

	*output_box = self->box;
	return (true);
}

t_hit_table_node	*concat_htn(t_hit_table_node *head, t_hit_table_node *tail)
{
	t_hit_table_node	*concat;

	if (!head)
		return (tail);
	if (!tail)
		return (head);
	concat = head;
	while (head->next)
		head = head->next;
	head->next = tail;
	return (concat);
}

void	append_htn(t_hit_table_node **head, t_hit_table_node *node)
{
	t_hit_table_node	*cur;

	if (!node)
		return ;
	if (!*head)
	{
		*head = node;
		return ;
	}
	cur = *head;
	while (cur->next)
		cur = cur->next;
	cur->next = node;
}

t_hit_table_node	*sort_htn(t_hit_table_node *head, t_hit_table_node *tail, bool (*comparator)(t_hit_table, t_hit_table))
{
	t_hit_table_node	*pivot;
	t_hit_table_node	*curr;
	t_hit_table_node	*next;
	t_hit_table_node	*less;
	t_hit_table_node	*greater;
	t_hit_table_node	*stop;

	if (!head || !head->next || head == tail)
		return (head);
	pivot = head;
	pivot->next = NULL;
	curr = head->next;
	less = NULL;
	greater = NULL;
	if (tail)
		stop = tail->next;
	else
		stop = NULL;
	while (curr && curr != stop)
	{
		next = curr->next;
		curr->next = NULL;
		if (comparator(*(curr->data), *(pivot->data)))
			append_htn(&less, curr);
		else
			append_htn(&greater, curr);
		curr = next;
	}
	less = sort_htn(less, NULL, comparator);
	greater = sort_htn(greater, NULL, comparator);
	pivot->next = greater;
	return (concat_htn(less, pivot));
}

t_hit_table_node	*get_nth_htn(t_hit_table_list *htl, size_t n)
{
	t_hit_table_node	*node;

	node = htl->head;
	while (node && 0 < n)
	{
		node = node->next;
		n--;
	}
	return (node);
}

t_hit_table_node	*skip_n_htn(t_hit_table_node *node, size_t n)
{
	while (node && 0 < n)
	{
		node = node->next;
		n--;
	}
	return (node);
}

t_bvh_node	*construct_bvh_node(t_hit_table_list *htl, size_t start, size_t end)
{
	t_bvh_node	*bvh_node;
	int			axis = random_int(0, 2);
	bool		(*comparator)(t_hit_table, t_hit_table);
	t_hit_table_node	*start_htn;

	bvh_node = calloc(1, sizeof(t_bvh_node));
	if (!bvh_node)
		return (NULL);
	bvh_node->hit_table.hit = hit_bvh;
	bvh_node->hit_table.bounding_box = bounding_bvh;
	start_htn = get_nth_htn(htl, start);
	if (axis == 0)
		comparator = box_x_compare; 
	else if (axis == 1)
		comparator = box_y_compare;
	else if (axis == 2)
		comparator = box_z_compare;
	size_t	object_span = end - start;
	if (object_span == 1) {
		bvh_node->left = start_htn->data;
		bvh_node->right = start_htn->data;
	} else if (object_span == 2) {
		if (comparator(*start_htn->data, *start_htn->next->data)) {
			bvh_node->left = start_htn->data;
			bvh_node->right = start_htn->next->data;
		} else {
			bvh_node->left = start_htn->next->data;
			bvh_node->right = start_htn->data;
		}
	} else {
		start_htn = sort_htn(start_htn, skip_n_htn(start_htn, end - start), comparator);
		size_t	mid = start + (end - start) / 2;
		bvh_node->left = construct_bvh_node(htl, start, mid);
		bvh_node->right = construct_bvh_node(htl, mid + 1, end); 
	}
	t_aabb	box_left;
	t_aabb	box_right;
	bvh_node->left->hit_table.bounding_box(bvh_node->left, \
			&box_left);
	bvh_node->right->hit_table.bounding_box(bvh_node->right, \
			&box_right);
	bvh_node->box = surrounding_box(box_left, box_right);
	return (bvh_node);
}
