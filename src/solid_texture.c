#include "texture.h"
#include <stdlib.h>

#include <stdio.h>
static t_color	texture_value_solid(void *s, double u, double v, t_point3 p);

t_solid_texture	construct_solid_texture(t_color color)
{
	t_solid_texture	solid;

	solid.texture.texture_value = texture_value_solid;
	solid.color = color;
	return (solid);
}

t_solid_texture	*gen_solid_texture(t_color color)
{
	t_solid_texture	*p = malloc(sizeof(*p));
	if (!p)
		return (NULL);
	*p = construct_solid_texture(color);
	return (p);
}

static t_color	texture_value_solid(void *s, double u, double v, t_point3 p)
{
	t_solid_texture	*self = s;
	(void)u;
	(void)v;
	(void)p;
	return (self->color);
}
