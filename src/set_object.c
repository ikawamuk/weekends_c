#include "material.h"
#include "sphere.h"
#include "libft.h"
#include "rt_utils.h"
#include "lambertian.h"
#include "bvh_info.h"
#include "hit_node.h"
#include "bvh.h"
#include <stdlib.h>
#include <stdio.h>

static bool		is_object(char *line);
static size_t	count_object_num(t_list *line_ptr);

int	set_objects(t_hit_table **node, t_list *line_lst)
{
	t_bvh_info	*object_array;
	size_t		array_size;

	array_size = count_object_num(line_lst);
	if (array_size == 0)
		return (EXIT_SUCCESS);
	object_array = (t_bvh_info *)calloc(array_size, sizeof(t_bvh_info));
	if (!object_array)
		return (perror("malloc"), EXIT_FAILURE);
	array_size = 0;
	while (line_lst)
	{
		if (is_object(line_lst->content))
			object_array[array_size++] = construct_bvh_info(line_lst->content);
		line_lst = line_lst->next;
	}
	*node = (t_hit_table *)gen_bvh(object_array, 0, array_size - 1);
	free(object_array);
	return (EXIT_SUCCESS);
}

static bool	is_object(char *line)
{
	static const char	*object_list[2] = {
		"sp", NULL
	};
	size_t	i;

	i = 0;
	while (object_list[i])
	{
		if (ft_strncmp(line, object_list[i], 2) == 0)
			return (true);
		i++;
	}
	return (false);
}

static size_t	count_object_num(t_list *line_lst)
{
	size_t	count;

	count = 0;
	while (line_lst)
	{
		if (is_object(line_lst->content))
			count++;
		line_lst = line_lst->next;
	}
	return (count);
}
