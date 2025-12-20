#include "vec3.h"
#include "rt_utils.h"
#include "libft.h"
#include <stdlib.h>

#include <stdio.h>

static void	err_sphere(void);

int	validate_sphere(char *line)
{
	size_t		i;
	double		d_tmp;
	int			i_tmp;

	if (skip_spaces(&line))
		return (err_sphere(), EXIT_FAILURE);
	i = 0;
	while (i++ < 3)
	{
		d_tmp = ft_strtod(line, &line);
		if (i != 3 && *(line++) != ',')
			return (err_sphere(), EXIT_FAILURE);
	}
	if (skip_spaces(&line))
		return (err_sphere(), EXIT_FAILURE);
	d_tmp = ft_strtod(line, &line);
	if (d_tmp <= 0)
		return (err_sphere(), EXIT_FAILURE);
	if (skip_spaces(&line))
		return (err_sphere(), EXIT_FAILURE);
	i = 0;
	while (i++ < 3)
	{
		i_tmp = ft_atoi(line);
		if ((i_tmp < 0 || 255 < i_tmp) || skip_digit(&line))
			return (err_sphere(), EXIT_FAILURE);
		if (i != 3 && *(line++) != ',')
			return (err_sphere(), EXIT_FAILURE);
	}
	if (*line == '\n' || *line == '\0')
		return (EXIT_SUCCESS);
	return (err_sphere(), EXIT_FAILURE);
}

static void	err_sphere(void)
{
	static char	*msg = \
"\x1b[31m""SET SPHERE'S INFORMATION CORRECTLY.\n" \
"\x1b[0m""sp [Center Coordinate] [diameter] " \
"\x1b[31m""R"",""\x1b[32m""G"",""\x1b[34m""B";

	ft_putendl_fd(msg, STDERR_FILENO);
}
