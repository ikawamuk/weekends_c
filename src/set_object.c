#include "libft.h"
#include "rt_utils.h"
#include "lambertian.h"
#include "hit_node.h"
#include "bvh.h"
#include <stdlib.h>
#include <stdio.h>

static bool		is_object(char *line);
static size_t	count_object_num(t_list *line_ptr);
t_hit_table		*get_object(char *line);

int	set_object(t_hit_table **node, t_list *line_lst)
{
	t_hit_table	**hit_table_array;
	size_t		array_size;

	array_size = count_object_num(line_lst);
	if (array_size == 0)
		return (EXIT_SUCCESS);
	hit_table_array = (t_hit_table **)calloc(array_size, sizeof(t_hit_table *));
	if (!hit_table_array)
		return (perror("malloc"), EXIT_FAILURE);
	array_size = 0;
	while (line_lst)
	{
		if (is_object(line_lst->content))
			hit_table_array[array_size++] = get_object(line_lst->content);
		line_lst = line_lst->next;
	}
	*node = gen_bvh(hit_table_array, 0, array_size - 1);
	free(hit_table_array);
	return (EXIT_SUCCESS);
}

static bool	is_object(char *line)
{
	static const char	*object_list[3] = {
		"sp", "L", NULL
	};
	static const size_t	object_len[2] = {
		2, 1
	};
	size_t	i;

	i = 0;
	while (object_list[i])
	{
		if (ft_strncmp(line, object_list[i], object_len[i]) == 0)
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
