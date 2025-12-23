#include "texture.h"
#include <stdlib.h>
#include "define.h"

static t_color	texture_value_bump(void *s, double u, double v, t_hit_record *rec);

t_bump_texture	construct_bump_texture()
{
	t_bump_texture	bump;

	bump.texture.texture_value = texture_value_bump;
	return (bump);
}

t_bump_texture	*gen_bump_texture()
{
	t_bump_texture	*p = malloc(sizeof(*p));
	if (!p)
		return (NULL);
	*p = construct_bump_texture();
	return (p);
}

static t_color	texture_value_bump(void *s, double u, double v, t_hit_record *rec)
{
	(void)s;
	t_vec3	onb[3];
	build_onb(onb, rec->normal);

	// --- 波のパラメータ ---
    double freq = 50.0;  // 波の細かさ（周波数）
    double strength = 0.05; // 凸凹の強さ

	double du = strength * cos(u * freq);
	double dv = strength * cos(v * freq);

	t_vec3 local_normal = add_vec(scal_mul_vec(onb[0], -du), add_vec(scal_mul_vec(onb[1], -dv), onb[2]));
	rec->normal = normalize(local_normal);
	return (construct_vec(0.5, 0.5, 0.5));
}
