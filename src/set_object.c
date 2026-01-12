#include "libft.h"
#include "rt_utils.h"
#include "lambertian.h"
#include "hit_node.h"
#include "bvh.h"
#include <stdlib.h>
#include <stdio.h>

static bool		is_aabb_object(char *line);
static bool		is_not_aabb_object(char *line);
static size_t	count_object_num(t_list *line_ptr);
t_hit_table		*get_object(char *line);
static int		set_one_object(t_hit_table **node, t_list *line_lst);
int				set_hs_object(t_hit_table **node, t_list *line_lst, bool (*is__object)(char *line));

t_hit_table	*gen_hit_node(t_hit_table *lhs, t_hit_table *rhs);

int	set_object(t_hit_table **node, t_list *line_lst)
{
	size_t		object_num;
	t_hit_table	*lhs;
	t_hit_table	*rhs;

	object_num = count_object_num(line_lst);
	if (object_num == 0)
		return (EXIT_SUCCESS);
	if (object_num == 1)
		return (set_one_object(node, line_lst));
	lhs = NULL;
	rhs = NULL;
	if (set_hs_object(&lhs, line_lst, is_aabb_object))
		return (EXIT_FAILURE);
	if (set_hs_object(&rhs, line_lst, is_not_aabb_object))
		return (lhs->clear(lhs), EXIT_FAILURE);
	*node = gen_hit_node(lhs, rhs);
	if (!*node)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/*
@brief aabbを持つ通常のオブジェクトはそのままBVHを構築する。
*/
int	set_hs_object(t_hit_table **node, t_list *line_lst, bool (*is__object)(char *line))
{
	t_hit_table	**hit_table_array;
	size_t		array_size;
	t_list		*line_lst_head;

	array_size = 0;
	line_lst_head = line_lst;
	while (line_lst)
	{
		if (is__object(line_lst->content))
			array_size++;
		line_lst = line_lst->next;
	}
	if (array_size == 0)
		return (EXIT_SUCCESS);
	hit_table_array = ft_calloc(array_size, sizeof(t_hit_table *));
	if (!hit_table_array)
		return (EXIT_SUCCESS);
	array_size = 0;
	line_lst = line_lst_head;
	while (line_lst)
	{
		if (is__object(line_lst->content))
			hit_table_array[array_size++] = get_object(line_lst->content);
		line_lst = line_lst->next;
	}
	*node = gen_bvh(hit_table_array, 0, array_size - 1);
	free(hit_table_array);
	return (EXIT_SUCCESS);
}

static bool	is_aabb_object(char *line)
{
	static const char	*object_list[5] = {
		"sp", "cy", "tr", "L", NULL
	};
	// フォンは光をhit_table_nodeに追加しない。
	// 突貫工事感あるからこの辺もう少しまともにしたい。
	static const char	*object_list_phong[4] = {
		"sp", "cy", "tr", NULL
	};
	static const size_t	object_len[4] = {
		2, 2, 2, 1
	};
	const char	**list;
	size_t		i;

	if (is_phong)
		list = (const char **)object_list_phong;
	else
		list = (const char **)object_list;
	i = 0;
	while (list[i])
	{
		if (ft_strncmp(line, object_list[i], object_len[i]) == 0)
			return (true);
		i++;
	}
	return (false);
}

static bool	is_not_aabb_object(char *line)
{
	static const char	*object_list[3] = {
		"pl", "co", NULL
	};
	static const size_t	object_len[2] = {
		2, 2
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

static bool	is_object(char *line)
{
	return (is_aabb_object(line) || is_not_aabb_object(line));
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

static int	set_one_object(t_hit_table **node, t_list *line_lst)
{
	while (line_lst)
	{
		if (is_object(line_lst->content))
		{
			*node = get_object(line_lst->content);
			return (EXIT_SUCCESS);
		}
		line_lst = line_lst->next;
	}
	return (EXIT_FAILURE);
}
