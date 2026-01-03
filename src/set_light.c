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

t_sphere				*get_light_data(char *line);
static bool				is_light(char *line);
// static t_hit_table_node	*add_light(t_hit_table_node *hit_table, char *line);

// t_hit_table_listはt_lstに変更したい。
int	set_light(t_hit_table_list *lights, t_list *line_lst)
{
	t_hit_table_list	list;
	void				*light_ptr;

	ft_bzero(&list, sizeof(t_hit_table_list));
	while (line_lst)
	{
		if (is_light(line_lst->content))
		{
			// printf("HERE1\n");
			light_ptr = (t_hit_table *)get_light_data(line_lst->content + 1);
			printf("light ptr: %p\n", light_ptr);
			if (!light_ptr || add_htl(&list, light_ptr) == false)
				return (clear_htl(list), \
				perror("malloc"), EXIT_FAILURE);
		}
		line_lst = line_lst->next;
	}
	*lights = construct_light_list();
	lights->head = list.head;
	return (EXIT_SUCCESS);
}

static bool	is_light(char *line)
{
	return (*line == 'L');
}

// static t_hit_table_node	*add_light(t_hit_table_node *hit_table, char *line)
// {
// 	t_hit_table_node	*new_node;

// 	new_node = calloc(1, sizeof(t_hit_table_node));
// 	if (!new_node)
// 		return (NULL);
// 	hit_table->next = new_node;
// 	new_node->data = (t_hit_table *)get_light_data(line + 1);
// 	return (new_node);
// }
