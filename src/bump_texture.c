#include "texture.h"
#include <stdlib.h>
#include "define.h"

static t_color	texture_value_bump(void *s, double u, double v, t_hit_record *rec);
// static double	height_sin(double u, double v);
// static double	height_random(double u, double v);
// static double	height_2d_sin(double u, double v);
static double height_ripples(double u, double v);
// static double	height_g(double u, double v);
// static double height_steps(double u, double v);
// static double height_fbm(double u, double v);
// static double	height_check(double u, double v);

t_bump_texture	construct_bump_texture(t_color color)
{
	t_bump_texture	bump;

	bump.texture.texture_value = texture_value_bump;
	bump.color = color;
	bump.height = height_ripples;
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
	static const double	eps = 0.01;
	t_vec3	onb[3];
	build_onb(onb, rec->normal);

	double	du = (self->height(u + eps, v) - self->height(u - eps, v)) / (2.0 * eps);
	double	dv = (self->height(u, v + eps) - self->height(u, v - eps)) / (2.0 * eps);

	t_vec3 local_normal = add_vec(scal_mul_vec(onb[0], -du * 0.03), add_vec(scal_mul_vec(onb[1], -dv * 0.03), scal_mul_vec(onb[2], 6)));
	rec->normal = normalize(local_normal);
	return (self->color);
}

// static double	height_sin(double u, double v)
// {
// 	(void)v;
// 	return sin(60.0 * M_PI * u);
// }

// static double	height_2d_sin(double u, double v)
// {
// 	static const double fleq = 30.0;
// 	return sin(fleq * M_PI * u) * sin(fleq * M_PI * v);
// }

// static double	height_random(double u, double v)
// {
// 	double x = u * 12.9898 + v * 78.233;
// 	return (fmod(sin(5 * x) * 43758.5453, 1.0));
// }

static double height_ripples(double u, double v)
{
	double d = sqrt(pow(u - 0.5, 2) + pow(v - 0.5, 2));
	return sin(100.0 * d);
}

// static double height_steps(double u, double v)
// {
// 	return floor(u * 10.0) / 10.0 + floor(v * 10.0) / 10.0;
// }

// static double height_fbm(double u, double v)
// {
// 	double h = 0;
// 	h += 3 * sin(20.0 * u) * sin(20.0 * v);
// 	h += 2 * sin(40.0 * u) * cos(40.0 * v);
// 	h += 1 * cos(80.0 * u) * sin(80.0 * v);
// 	return h;
// }

// static double	height_check(double u, double v)
// {
// 	int	iu = floor(u);
// 	int	iv = floor(v);

// 	if ((iu + iv) & 1)
// 		return (0);
// 	else
// 		return (1);
// }



