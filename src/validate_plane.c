#include "vec3.h"
#include "rt_utils.h"
#include "libft.h"
#include <stdlib.h>

#include <stdio.h>

static void	err_plane(void);

int	validate_plane(char *line)
{
	if (skip_spaces(&line))
		return (err_plane(), EXIT_FAILURE);
	if (skip_vec(&line, IS_POINT))
		return (err_plane(), EXIT_FAILURE);
	if (skip_spaces(&line))
		return (err_plane(), EXIT_FAILURE);
	if (skip_vec(&line, IS_UNIT))
		return (err_plane(), EXIT_FAILURE);
	if (skip_spaces(&line))
		return (err_plane(), EXIT_FAILURE);
	if (skip_vec(&line, IS_COLOR))
		return (err_plane(), EXIT_FAILURE);
	if (*line == '\n' || *line == '\0')
		return (EXIT_SUCCESS);
	return (err_plane(), EXIT_FAILURE);
}

static void	err_plane(void)
{
	static char	*msg = \
"\x1b[31m""SET PLANE'S INFORMATION CORRECTLY.\n" \
"\x1b[0m""sp [CORDINATE IN THE PLANE] [3D NORMALIZED NORMAL VECTOR] " \
"\x1b[31m""R"",""\x1b[32m""G"",""\x1b[34m""B";

	ft_putendl_fd(msg, STDERR_FILENO);
}
