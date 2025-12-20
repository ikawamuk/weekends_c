#include "hit_table_list.h"
#include "rt_utils.h"

static bool		hit_htl(const void *s, const t_ray ray, t_hit_record *rec, t_range range);
static double	pdf_value_lights(void *s, t_point3 p, t_vec3 direction);
static t_vec3	random_lights(void *s, t_point3 p);

t_hit_table_list	construct_htl(void)
{
	t_hit_table_list	list;

	list.hit_table.hit = hit_htl;
	list.head = NULL;
	return (list);
}

t_hit_table_list	construct_light_list(void)
{
	t_hit_table_list	lights;

	lights.hit_table.hit = hit_htl;
	lights.hit_table.pdf_value = pdf_value_lights;
	lights.hit_table.random = random_lights;
	lights.head = NULL;
	return (lights);
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

static bool	hit_htl(const void *s, const t_ray ray, t_hit_record *rec, t_range range)
{
	const t_hit_table_list	*self = s;
	t_hit_table_node	*tail_p = self->head;
	t_hit_record		temp_rec;
	bool				hit_anything = false;

	while (tail_p)
	{
		if (!tail_p->data)
			continue ;
		if (tail_p->data->hit(tail_p->data, ray, &temp_rec, range))
		{
			hit_anything = true;
			range.max = temp_rec.t;
			*rec = temp_rec;
		}
		tail_p = tail_p->next;
	}
	return (hit_anything);
}

static double	pdf_value_lights(void *s, t_point3 p, t_vec3 direction)
{
	const t_hit_table_list	*self = s;
	t_hit_table_node		*tail_p = self->head;
	double					pdf_sum = 0;

	while (tail_p)
	{
		if (tail_p->data)
			pdf_sum += tail_p->data->pdf_value(tail_p->data, p, direction);
		tail_p = tail_p->next;
	}
	return (pdf_sum);
}

static int		count_hit_table_list(t_hit_table_list list)
{
	t_hit_table_node	*node = list.head;
	int					count = 0;

	while (node)
	{
		if (node->data)
			count++;
		node = node->next;
	}
	return (count);
}

static t_vec3	random_lights(void *s, t_point3 p)
{
	const t_hit_table_list	*self = s;
	int						count = count_hit_table_list(*self);
	if (count == 0)
		return (construct_vec(0, 0, 0));
	int	target = random_int(0, count - 1);
	int i = 0;
	t_hit_table_node	*node = self->head;
	while (node)
	{
		if (node->data)
			if (i++ == target)
				return (node->data->random(node->data, p));
		node = node->next;
	}
	return (construct_vec(0, 0, 0));
}
