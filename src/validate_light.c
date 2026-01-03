#include "vec3.h"
#include "rt_utils.h"
#include "range.h"
#include "libft.h"
#include <stdlib.h>

#include <stdio.h>

static void	err_light(void);

int	validate_light(char *line)
{
	if (skip_spaces(&line))
		return (err_light(), EXIT_FAILURE);
	if (skip_vec(&line, IS_POINT))
		return (err_light(), EXIT_FAILURE);
	if (skip_spaces(&line))
		return (err_light(), EXIT_FAILURE);
	if (skip_range(&line, 0, 1) == false) // light brightness ratio
		return (err_light(), EXIT_FAILURE);
	if (skip_spaces(&line))
		return (err_light(), EXIT_FAILURE);
	if (skip_vec(&line, IS_COLOR))
		return (err_light(), EXIT_FAILURE);
	skip_spaces(&line);
	if (*line == '\n' || *line == '\0')
		return (EXIT_SUCCESS);
	return (err_light(), EXIT_FAILURE);
}

static void	err_light(void)
{
	static char	*msg = \
"\x1b[31m""SET LIGHT'S INFORMATION CORRECTLY.\n" \
"\x1b[0m""L [Center Coordinate] [light brightness ratio 0-1]" \
"\x1b[31m""R"",""\x1b[32m""G"",""\x1b[34m""B""\x1b[0m";

	ft_putendl_fd(msg, STDERR_FILENO);
}
