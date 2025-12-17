#include "vec3.h"
#include "ray.h"
#include "hit_table_list.h"
#include "material.h"
#include "util.h"
#include "world.h"

static bool	killed_by_russian_roulette(t_color *attenuation);

t_color ray_color(t_ray ray, const t_world *world, int depth)
{
	t_hit_record	rec;

	if (depth >= MAX_DEPTH)
		return (construct_color(0, 0, 0));
	if (!world->objects.hit_table.hit(&world->objects, ray, &rec))
		return (world->back_ground);
	t_scatter_record	srec;
	t_color	emmited = rec.mat_ptr->emitted(rec.mat_ptr, rec);
	if (!rec.mat_ptr->scatter(rec.mat_ptr, rec, &srec))
		return (emmited);
	if (depth > RR_START_DEPTH && killed_by_russian_roulette(&srec.attenuation))
		return (emmited);
	// Color_ o = emmited + Albdo * Color_i(scattered) --> Color_o = emmited + {(Albedo * Color_i(scattered)) * (surface_pdf / sampling_pdf)} に変更したい
	// Befor: return (add_vec(emmited, mul_vec(srec.attenuation, ray_color(srec.scattered, world, depth + 1))));
	return (add_vec(emmited, scal_mul_vec(mul_vec(srec.attenuation, ray_color(srec.scattered, world, depth + 1)), \
							(rec.mat_ptr->surface_pdf(&rec.mat_ptr, rec, srec.scattered) / srec.sampling_pdf))));
}

static bool	killed_by_russian_roulette(t_color *attenuation)
{
	double	live_probability = fmax(fmax(attenuation->x, attenuation->y), attenuation->z);
	live_probability = clamp(live_probability, LIVE_PROBABILITY_MIN, 1.0);
	if (live_probability <= random_double(0, 1))
		return (true);
	*attenuation = scal_div_vec(*attenuation, live_probability);
	return (false);
}
