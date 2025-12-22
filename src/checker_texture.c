#include "texture.h"
#include <stdlib.h>
#include <math.h>
#include "define.h"

static t_color	texture_value_check(void *s, double u, double v, t_point3 p);

t_checker_texture	construct_checker_texture(void *even_texture, void *odd_texture)
{
	t_checker_texture	check;

	check.texture.texture_value = texture_value_check;
	check.even = even_texture;
	check.odd = odd_texture;
	return (check);
}

t_checker_texture	*gen_checker_texture(void *even_texture, void *odd_texture)
{
	t_checker_texture	*p = malloc(sizeof(*p));
	if (!p)
		return (NULL);
	*p = construct_checker_texture(even_texture, odd_texture);
	return (p);
}

static t_color	texture_value_check(void *s, double u, double v, t_point3 p)
{
	t_checker_texture	*self = s;

	double	sines = sin(10.0 * (p.x + DBL_EPSILON)) * sin(10.0 * (p.x + DBL_EPSILON)) * sin(10.0 * (p.x + DBL_EPSILON));
	if (sines < 0)
		return (self->odd->texture_value(self->odd, u, v, p));
	else
		return (self->even->texture_value(self->even, u, v, p));
}
