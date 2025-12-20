#include "libft.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

int			validate_ambient(char *line);
int			validate_camera(char *line);
int			validate_sphere(char *line);
static int	distribute_validate(char *line);
void		err_distribute(void);

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
	// if (*line == 'L')
	// 	return (validate_light);
	if (ft_strncmp(line, "sp", 2) == 0)
		return (validate_sphere(line + 2));
	err_distribute();
	return (EXIT_FAILURE);
}

void	err_distribute(void)
{
	static char	*msg = "KEEP .rt's FORMAT CORRECTLY.";

	ft_putendl_fd(msg, STDERR_FILENO);
}
