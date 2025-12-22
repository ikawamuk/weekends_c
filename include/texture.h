#ifndef TEXTURE_H
# define TEXTURE_H

#include "vec3.h"

typedef struct s_texture
{
	t_color	(*texture_value)(void *self, double u, double v, t_point3 p);
}	t_texture;

typedef struct s_solid_texture
{
	t_texture	texture;
	t_color		color;
}	t_solid_texture;

t_solid_texture	*gen_solid_texture(t_color color);

typedef struct s_checker_texture
{
	t_texture	texture;
	t_texture	*even;
	t_texture	*odd;
}	t_checker_texture;

t_checker_texture	*gen_checker_texture(void *even_texture, void *odd_texture);

#endif
