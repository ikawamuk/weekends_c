#include "vec3.h"
#include "ray.h"
#include "hit_table_list.h"
#include "material.h"
#include "rt_utils.h"
#include "world.h"

static bool	killed_by_russian_roulette(t_color *attenuation);

t_color ray_color(t_ray ray, const t_world *world, int depth)
{
	t_hit_record	rec;

	if (depth >= MAX_DEPTH)
		return (construct_color(0, 0, 0));
	if (!world->objects.hit_table.hit(&world->objects, ray, &rec, (t_t_range){HIT_T_MIN, INFINITY}))
		return (world->back_ground);
	t_ray	scattered;
	t_color	attenuation;
	t_color	emmited = rec.mat_ptr->emitted(rec.mat_ptr, rec);
	if (!rec.mat_ptr->scatter(rec.mat_ptr, rec, &attenuation, &scattered))
		return (emmited);
	if (depth > RR_START_DEPTH && killed_by_russian_roulette(&attenuation))
		return (emmited);
	return (add_vec(emmited, mul_vec(attenuation, ray_color(scattered, world, depth + 1))));
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
