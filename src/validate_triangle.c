#include "rt_utils.h"
#include "range.h"
#include "libft.h"
#include <stdlib.h>

static void		err_triangle(void);

int	validate_triangle(char *line)
{
	if (skip_spaces(&line))
		return (err_triangle(), EXIT_FAILURE);
	if (skip_vec(&line, IS_POINT))
		return (err_triangle(), EXIT_FAILURE);
	if (skip_spaces(&line))
		return (err_triangle(), EXIT_FAILURE);
	if (skip_vec(&line, IS_POINT))
		return (err_triangle(), EXIT_FAILURE);
	if (skip_spaces(&line))
		return (err_triangle(), EXIT_FAILURE);
	if (skip_vec(&line, IS_POINT))
		return (err_triangle(), EXIT_FAILURE);
	if (skip_spaces(&line))
		return (err_triangle(), EXIT_FAILURE);
	if (skip_vec(&line, IS_COLOR))
		return (err_triangle(), EXIT_FAILURE);
	skip_spaces(&line);
	if (*line == '\n' || *line == '\0')
		return (EXIT_SUCCESS);
	return (err_triangle(), EXIT_SUCCESS);
}

static void	err_triangle(void)
{
	static char	*msg = \
"\x1b[31m""SET TRIANGLE'S INFORMATION CORRECTLY.\n" \
"\x1b[0m""tr [Coordinate1]\t[Coordinate2]\t[Coordinate3]\t" \
"\x1b[31m""R"",""\x1b[32m""G"",""\x1b[34m""B";

	ft_putendl_fd(msg, STDERR_FILENO);
}
