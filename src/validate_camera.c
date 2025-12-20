#include "rt_utils.h"
#include "libft.h"
#include <stdlib.h>

static double	double_abs(double a);
static void		err_camera(void);

// You need to imprement new function
// which return true if two doubles are almost equal
// but in the first place, libft doesn't
// have fabs nor strtof so...
int	validate_camera(char *line)
{
	double	d_tmp;
	size_t	i;

	i = 0;
	while (i++ < 3)
	{
		d_tmp = ft_strtod(line, &line);
		if (i != 3 && *(line++) != ',')
			return (err_camera(), EXIT_FAILURE);
	}
	if (skip_spaces(&line))
		return (err_camera(), EXIT_FAILURE);
	i = 0;
	d_tmp = 0;
	while (i++ < 3)
	{
		d_tmp += pow2(ft_strtod(line, &line));
		if (i != 3 && *(line++) != ',')
			return (err_camera(), EXIT_FAILURE);
	}
	if (0.001 < double_abs(d_tmp - 1))
		return (err_camera(), EXIT_FAILURE);
	if (skip_spaces(&line))
		return (err_camera(), EXIT_FAILURE);
	d_tmp = ft_strtod(line, &line);
	if (d_tmp < 0.0f || 180.0f < d_tmp)
		return (err_camera(), EXIT_FAILURE);
	if (*line == '\n' || *line == '\0')
		return (EXIT_SUCCESS);
	return (err_camera(), EXIT_SUCCESS);
}

static double	double_abs(double a)
{
	if (a < 0.0f)
		return (-a);
	return (a);
}

static void	err_camera(void)
{
	static char	*msg = \
"\x1b[31m""SET CAMARA'S INFORMATION CORRECTLY.\n" \
"\x1b[0m""C [Coordinate]\t[Unit Direction Vector]\t[Vertical FOV(0-180)]\n" \
"\x1b[0m""C 0,0,0\t\t0,-1,0\t\t\t70";

	ft_putendl_fd(msg, STDERR_FILENO);
}
