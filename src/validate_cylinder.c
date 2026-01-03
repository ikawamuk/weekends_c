#include "rt_utils.h"
#include "libft.h"
#include <stdlib.h>

#include <stdio.h>

static void	err_cylinder(void);

int	validate_cylinder(char *line)
{
	if (skip_spaces(&line))
		return (err_cylinder(), EXIT_FAILURE);
	if (skip_vec(&line, IS_POINT))
		return (err_cylinder(), EXIT_FAILURE);
	if (skip_spaces(&line))
		return (err_cylinder(), EXIT_FAILURE);
	if (skip_vec(&line, IS_UNIT))
		return (err_cylinder(), EXIT_FAILURE);
	if (skip_spaces(&line))
		return (err_cylinder(), EXIT_FAILURE);
	if (ft_strtod(line, &line) <= 0) // diameter
		return (err_cylinder(), EXIT_FAILURE);
	if (skip_spaces(&line))
		return (err_cylinder(), EXIT_FAILURE);
	if (ft_strtod(line, &line) <= 0) // height
		return (err_cylinder(), EXIT_FAILURE);
	if (skip_spaces(&line))
		return (err_cylinder(), EXIT_FAILURE);
	if (skip_vec(&line, IS_COLOR))
		return (err_cylinder(), EXIT_FAILURE);
	skip_spaces(&line);
	if (*line == '\n' || *line == '\0')
		return (EXIT_SUCCESS);
	return (err_cylinder(), EXIT_FAILURE);
}

static void	err_cylinder(void)
{
	static char	*msg = \
"\x1b[31m""SET CYLINDER'S INFORMATION CORRECTLY.\n" \
"\x1b[0m""sp [Center Coordinate] [normalized vector of axis of cylinder] [diameter] [height] " \
"\x1b[31m""R"",""\x1b[32m""G"",""\x1b[34m""B""\x1b[0m";

	ft_putendl_fd(msg, STDERR_FILENO);
}
