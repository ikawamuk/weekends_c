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
static int	distribute_validate(char *line);
void		err_distribute(char *line);

// もしカメラとambientがセットされていなかったらエラー
// にするように要修正。
int	validate(t_list *line_lst)
{
	while (line_lst)
	{
		if (distribute_validate(line_lst->content))
			return (EXIT_FAILURE);
		line_lst = line_lst->next;
	}
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
	err_distribute(line);
	return (EXIT_FAILURE);
}

/*
@param line invalid identifered line
*/
void	err_distribute(char *line)
{
	static char	*msg = "SET .rt's FORMAT CORRECTLY.";

	ft_putstr_fd(line, STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
}
