#include "texture.h"
#include <stdlib.h>
#include <math.h>
#include "define.h"

static t_color	texture_value_check(void *s, double u, double v, t_hit_record rec);

t_checker_texture	construct_checker_texture(void *even_texture, void *odd_texture, int scale)
{
	t_checker_texture	check;

	check.texture.texture_value = texture_value_check;
	check.even = even_texture;
	check.odd = odd_texture;
	check.scale = scale;
	return (check);
}

t_checker_texture	*gen_checker_texture(void *even_texture, void *odd_texture, int scale)
{
	t_checker_texture	*p = malloc(sizeof(*p));
	if (!p)
		return (NULL);
	*p = construct_checker_texture(even_texture, odd_texture, scale);
	return (p);
}

static t_color	texture_value_check(void *s, double u, double v, t_hit_record rec)
{
	t_checker_texture	*self = s;
	int iu = (int)floor(u * self->scale);
	int iv = (int)floor(v * self->scale);

	if ((iu + iv) & 1)
		return (self->odd->texture_value(self->odd, u, v, rec));
	else
		return (self->even->texture_value(self->even, u, v, rec));
}
