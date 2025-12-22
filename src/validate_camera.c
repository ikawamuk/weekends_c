#include "rt_utils.h"
#include "range.h"
#include "libft.h"
#include <stdlib.h>

static void		err_camera(void);

int	validate_camera(char *line)
{
	if (skip_spaces(&line))
		return (err_camera(), EXIT_FAILURE);
	if (skip_vec(&line, IS_POINT))
		return (err_camera(), EXIT_FAILURE);
	if (skip_spaces(&line))
		return (err_camera(), EXIT_FAILURE);
	if (skip_vec(&line, IS_UNIT)) // unit vec
		return (err_camera(), EXIT_FAILURE);
	if (skip_spaces(&line))
		return (err_camera(), EXIT_FAILURE);
	if (skip_range(&line, 0, 180) == false) // vertical fov
		return (err_camera(), EXIT_FAILURE);
	if (*line == '\n' || *line == '\0')
		return (EXIT_SUCCESS);
	return (err_camera(), EXIT_SUCCESS);
}

static void	err_camera(void)
{
	static char	*msg = \
"\x1b[31m""SET CAMARA'S INFORMATION CORRECTLY.\n" \
"\x1b[0m""C [Coordinate]\t[Unit Direction Vector]\t[Vertical FOV(0-180)]\n" \
"\x1b[0m""C 0,0,0\t\t0,-1,0\t\t\t70";

	ft_putendl_fd(msg, STDERR_FILENO);
}
