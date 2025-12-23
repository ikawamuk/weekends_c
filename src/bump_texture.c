#include "texture.h"
#include <stdlib.h>
#include "define.h"

static t_color	texture_value_bump(void *s, double u, double v, t_hit_record *rec);


static t_vec3	local_normal_checker(double u, double v);

t_bump_texture	construct_bump_texture(t_color color)
{
	t_bump_texture	bump;

	bump.texture.texture_value = texture_value_bump;
	bump.color = color;
	bump.local_normal = local_normal_checker;
	return (bump);
}

t_bump_texture	*gen_bump_texture(t_color color)
{
	t_bump_texture	*p = malloc(sizeof(*p));
	if (!p)
		return (NULL);
	*p = construct_bump_texture(color);
	return (p);
}

static t_color	texture_value_bump(void *s, double u, double v, t_hit_record *rec)
{
	t_bump_texture	*self = s;
	t_vec3			onb[3];
	build_onb(onb, rec->normal);

	t_vec3	unit_local_normal = normalize(self->local_normal(u, v));
	rec->normal = local_onb(onb, unit_local_normal);
	return (self->color);
}

static t_vec3	local_normal_checker(double u, double v)
{
	static double scale = 100.0;
	u *= scale;
	v *= scale;
	int	iu = floor(u);
	int	iv = floor(v);

	if ((iu + iv) & 1)
		return (construct_vec(u - floor(u), 0, 0.1));
	return (construct_vec(floor(u) - u, 0, 0.1));
}
