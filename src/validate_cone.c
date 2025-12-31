#include "vec3.h"
#include "rt_utils.h"
#include "libft.h"
#include <stdlib.h>

static void	err_cone(void);

int	validate_cone(char *line)
{
	if (skip_spaces(&line))
		return (err_cone(), EXIT_FAILURE);
	if (skip_vec(&line, IS_POINT))
		return (err_cone(), EXIT_FAILURE);
	if (skip_spaces(&line))
		return (err_cone(), EXIT_FAILURE);
	if (skip_vec(&line, IS_UNIT))
		return (err_cone(), EXIT_FAILURE);
	if (skip_spaces(&line))
		return (err_cone(), EXIT_FAILURE);
	if (skip_range(&line, 0, 89) == false) // half vertex angle
		return (err_cone(), EXIT_FAILURE);
	if (skip_spaces(&line))
		return (err_cone(), EXIT_FAILURE);
	if (skip_vec(&line, IS_COLOR))
		return (err_cone(), EXIT_FAILURE);
	if (*line == '\n' || *line == '\0')
		return (EXIT_SUCCESS);
	return (err_cone(), EXIT_FAILURE);
}

static void	err_cone(void)
{
	static char	*msg = \
"\x1b[31m""SET CONE'S INFORMATION CORRECTLY.\n" \
"\x1b[0m""sp [CENTER OF CONE] [3D NORMALIZED NORMAL VECTOR OF AXIS] [HALF ANGLE 0-89]" \
"\x1b[31m""R"",""\x1b[32m""G"",""\x1b[34m""B";

	ft_putendl_fd(msg, STDERR_FILENO);
}
