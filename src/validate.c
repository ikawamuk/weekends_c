#include "libft.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

int			validate_ambient(char *line);
int			validate_camera(char *line);
int			validate_light(char *line);
int			validate_cylinder(char *line);
int			validate_plane(char *line);
int			validate_sphere(char *line);
int			validate_cone(char *line);
static int	distribute_validate(char *line);
void		err_distribute(void);
void		err_set(char *object);

// もしカメラとambientがセットされていなかったらエラー
// にするように要修正。
int	validate(t_list *line_lst)
{
	int	c_set;
	int	a_set;

	c_set = 0;
	a_set = 0;
	while (line_lst)
	{
		if (*(char *)(line_lst->content) == 'C')
			c_set++;
		if (*(char *)(line_lst->content) == 'A')
			a_set++;
		if (distribute_validate(line_lst->content))
			return (EXIT_FAILURE);
		line_lst = line_lst->next;
	}
	if (a_set == 0)
		err_set("Ambient lighting");
	if (c_set == 0)
		err_set("Camera");
	if (a_set == 0 || c_set == 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	distribute_validate(char *line)
{
	if (*line == 'A')
		return (validate_ambient(line + 1));
	if (*line == 'C')
		return (validate_camera(line + 1));
	if (*line == 'L')
		return (validate_light(line + 1));
	if (ft_strncmp(line, "sp", 2) == 0)
		return (validate_sphere(line + 2));
	if (ft_strncmp(line, "cy", 2) == 0)
		return (validate_cylinder(line + 2));
	if (ft_strncmp(line, "pl", 2) == 0)
		return (validate_plane(line + 2));
	if (ft_strncmp(line, "co", 2) == 0)
		return (validate_cone(line + 2));
	err_distribute();
	return (EXIT_FAILURE);
}

void	err_distribute(void)
{
	static char	*msg = "SET .rt's FORMAT CORRECTLY.";

	ft_putendl_fd(msg, STDERR_FILENO);
}

void	err_set(char *object)
{
	ft_putstr_fd("SET ", STDERR_FILENO);
	ft_putendl_fd(object, STDERR_FILENO);
}
