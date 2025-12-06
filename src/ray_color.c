#include "vec3.h"
#include "ray.h"
#include "hit_table_list.h"
#include "material.h"
#include "util.h"

static t_color	attenuated_ray_color(t_hit_table_list *world, t_ray scattered, t_color attenuation, int depth);

t_color ray_color(const t_ray ray, t_hit_table_list *world, int depth)
{
	t_hit_record	rec;

	if (depth >= MAX_DEPTH)
		return (construct_color(0, 0, 0));
	if (world->hit_table.hit(world, ray, &rec))
	{
		t_ray	scattered;
		t_color	attenuation;
		if (rec.mat_ptr->scatter(rec.mat_ptr, rec, &attenuation, &scattered))
			return (attenuated_ray_color(world, scattered, attenuation, depth));
		return (construct_color(0,0,0));
	}
	t_vec3	unit_direction = normalize(ray.direct);
	double	t = 0.5 * (unit_direction.y + 1.0);
	return (add_vec(scal_mul_vec(construct_color(1.0, 1.0, 1.0), (1.0 - t)), scal_mul_vec(construct_color(0.5, 0.7, 1.0), t)));
}

static t_color	attenuated_ray_color(t_hit_table_list *world, t_ray scattered, t_color attenuation, int depth)
{
	if (depth > RR_START_DEPTH)
	{
		double	live_probability = fmax(fmax(attenuation.x, attenuation.y), attenuation.z);
		live_probability = clamp(live_probability, LIVE_PROBABILITY_MIN, 1.0);
		if (live_probability <= random_double(0, 1))
			return (construct_color(0,0,0));
		attenuation = scal_div_vec(attenuation, live_probability);
	}
	return (mul_vec(attenuation, ray_color(scattered, world, depth + 1)));
}
