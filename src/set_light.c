#include "define.h"
#include "material.h"
#include "light.h"
#include "sphere.h"
#include "libft.h"
#include "rt_utils.h"
#include "hit_table_list.h"
#include "bvh.h"
#include <stdlib.h>
#include <stdio.h>

static bool				is_light(char *line);
static t_hit_table_node	*add_light(t_hit_table_node *hit_table, char *line);

int	set_light(t_hit_table_list *lights, t_list *line_lst)
{
	t_hit_table_node	*curr;
	t_hit_table_node	head;

	ft_bzero(&head, sizeof(t_hit_table));
	curr = &head;
	while (line_lst && curr)
	{
		if (is_light(line_lst->content))
			curr = add_light(curr, line_lst->content);
		line_lst = line_lst->next;
	}
	if (!curr)
		return (perror("malloc"), EXIT_FAILURE);
	*lights = construct_light_list();
	lights->head = head.next;
	return (EXIT_SUCCESS);
}

static bool	is_light(char *line)
{
	return (*line == 'L');
}

t_sphere	*get_light_data(char *line);

static t_hit_table_node	*add_light(t_hit_table_node *hit_table, char *line)
{
	t_hit_table_node	*new_node;

	new_node = calloc(1, sizeof(t_hit_table_node));
	if (!new_node)
		return (NULL);
	hit_table->next = new_node;
	new_node->data = (t_hit_table *)get_light_data(line + 1);
	return (new_node);
}
