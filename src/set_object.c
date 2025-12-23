#include "libft.h"
#include "rt_utils.h"
#include "lambertian.h"
#include "hit_node.h"
#include "bvh.h"
#include <stdlib.h>
#include <stdio.h>

static bool		is_aabb_object(char *line);
static size_t	count_object_num(t_list *line_ptr);
t_hit_table		*get_object(char *line);
static int		set_aabb_object(t_hit_table **node, t_list *line_lst, t_hit_table **hit_table_array);
static int		set_no_aabb_object(t_hit_table **node, t_list *line_lst, t_hit_table **hit_table_array);

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
	set_aabb_object(node, line_lst, hit_table_array);
	set_no_aabb_object(node, line_lst, hit_table_array);
	free(hit_table_array);
	return (EXIT_SUCCESS);
}

/*
@brief aabbを持つ通常のオブジェクトはそのままBVHを構築する。
*/
int	set_aabb_object(t_hit_table **node, t_list *line_lst, t_hit_table **hit_table_array)
{
	size_t	aabb_array_size;

	aabb_array_size = 0;
	while (line_lst)
	{
		if (is_aabb_object(line_lst->content))
			hit_table_array[aabb_array_size++] = get_object(line_lst->content);
		line_lst = line_lst->next;
	}
	if (hit_table_array == 0)
		return (EXIT_SUCCESS);
	*node = gen_bvh(hit_table_array, 0, aabb_array_size - 1);
	return (EXIT_SUCCESS);
}

/*
@brief aabbを持たない無限プリミティブは右側にまとめて保持する。
*/
static int	set_no_aabb_object(t_hit_table **node, t_list *line_lst, t_hit_table **hit_table_array)
{
	size_t		no_aabb_array_size;
	t_hit_node	*root;
	t_hit_table	*right;

	no_aabb_array_size = 0;
	while (line_lst)
	{
		if (ft_strncmp(line_lst->content, "pl", 2) == 0)
			hit_table_array[no_aabb_array_size++] = get_object(line_lst->content);
		line_lst = line_lst->next;
	}
	if (no_aabb_array_size == 0)
		return (EXIT_SUCCESS);
	right = gen_bvh(hit_table_array, 0, no_aabb_array_size - 1);
	if (*node == NULL)
	{
		*node = right;
		return (EXIT_SUCCESS);
	}
	root = ft_calloc(1, sizeof(t_hit_node));
	root->lhs = (t_hit_table *)*node;
	root->rhs = (t_hit_table *)right;
	root->hit_table = construct_bvh_htl(root);
	*node = (t_hit_table *)root;
	return (EXIT_SUCCESS);
}

static bool	is_aabb_object(char *line)
{
	static const char	*object_list[4] = {
		"sp", "cy", "L", NULL
	};
	static const size_t	object_len[3] = {
		2, 2, 1
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
	return (is_aabb_object(line) || ft_strncmp(line, "pl", 2) == 0);
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
