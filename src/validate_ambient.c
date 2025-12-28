#include "rt_utils.h"
#include "range.h"
#include "libft.h"
#include <stddef.h>
#include <stdlib.h>

static void	err_ambient(char *line);

int	validate_ambient(char *line)
{
	if (skip_spaces(&line))
		return (err_ambient(line), EXIT_FAILURE);
	if (skip_range(&line, 0, 1) == false) // light brightness ratio
		return (err_ambient(line), EXIT_FAILURE);
	if (skip_spaces(&line))
		return (err_ambient(line), EXIT_FAILURE);
	if (skip_vec(&line, IS_COLOR))
		return (err_ambient(line), EXIT_FAILURE);
	if (*line == '\n' || *line == '\0')
		return (EXIT_SUCCESS);
	return (err_ambient(line), EXIT_FAILURE);
}

//necessary to implement strtod
static void	err_ambient(char *line)
{
	static char	*msg = \
"SET AMBIENT CORRECTLY.\n" \
"\x1b[0m""A [lighting ratio] ""\x1b[31m""R"",""\x1b[32m""G"",""\x1b[34m""B""\x1b[0m";

	ft_putendl_fd(msg, STDERR_FILENO);
	ft_putendl_fd(line, STDERR_FILENO);
}
