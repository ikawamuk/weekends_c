#include "texture.h"
#include <stdlib.h>
#include "define.h"

static t_color	texture_value_bump(void *s, double u, double v, t_hit_record *rec);


// static t_vec3	local_normal_checker(double u, double v);
// static t_vec3	local_normal_sin(double u, double v);
static t_vec3	local_normal_ripple(double u, double v);

t_bump_texture	construct_bump_texture(t_color color)
{
	t_bump_texture	bump;

	bump.texture.texture_value = texture_value_bump;
	bump.color = color;
	bump.local_normal = local_normal_ripple;
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

// static t_vec3	local_normal_checker(double u, double v)
// {
// 	static double frequency = 100.0;
// 	u *= frequency;
// 	v *= frequency;
// 	int	iu = floor(u);
// 	int	iv = floor(v);

// 	if ((iu + iv) & 1)
// 		return (construct_vec(u - floor(u), 0, 0.2));
// 	return (construct_vec(floor(u) - u, 0, 0.2));
// }

// static t_vec3	local_normal_sin(double u, double v)
// {
// 	static double frequency = 100.0;
// 	double strength = 2.0;

// 	double	du = cos(u * frequency) * strength;
// 	double	dv = cos(v * frequency) * strength;
// 	return (construct_vec(du, dv, 1.0));
// }

static t_vec3	local_normal_ripple(double u, double v)
{
	static double frequency = 400.0;
	double strength = 2.0;

	double	r = sqrt(u * u + v * v);
	double	ripple = cos(r * frequency) * strength;

	double	du = (r == 0) ? 0 : (u / r) * ripple;
	double	dv = (r == 0) ? 0 : (v / r) * ripple;
	return (construct_vec(du, dv, 1.0));
}

// レンガ
// static t_color	texture_value_bump(void *s, double u, double v, t_hit_record *rec)
// {
// 	t_bump_texture *self = s;
// 	double	gap = 0.05;
// 	double	ver = 10.0;
// 	double	hori = 20.0;

// 	t_vec3	position = construct_vec(u * ver, v * hori, 0);
// 	if (fmod(floor(position.y), 2.0) > 0.5)
// 		position.x += 0.5;
// 	t_vec3	st = construct_vec(fmod(position.x, 1), fmod(position.y, 1), 0);
// 	double	horizontal = smooth_step(0, gap, st.x) * smooth_step(0, gap, 1.0 - st.x);
// 	double	vertical = smooth_step(0, gap, st.y) * smooth_step(0, gap, 1.0 - st.y);

// 	(void)rec; // 法線ベクトルは未実装
// 	return (scal_mul_vec(self->color, horizontal * vertical));
// }