#include "vec3.h"
#include "ray.h"
#include "hit_table_list.h"
#include "material.h"
#include "util.h"
#include "world.h"
#include "pdf.h"


#include <stdio.h>
static bool	killed_by_russian_roulette(t_color *attenuation);

/*
@brief Color_i = Albedo * Color_o * surface_pdf / sampling_pdf; 
@brief and generate scatter ray
*/
t_color ray_color(t_ray ray, const t_world *world, int depth)
{
	t_hit_record	rec;

	if (depth >= MAX_DEPTH)
		return (construct_color(0, 0, 0));
	if (!world->objects.hit_table.hit(&world->objects, ray, &rec))
		return (world->back_ground);

	t_color	emmited = rec.mat_ptr->emitted(rec.mat_ptr, rec);

	t_scatter_record	srec;
	if (!rec.mat_ptr->scatter(rec.mat_ptr, rec, &srec))
		return (emmited);
	if (depth > RR_START_DEPTH && killed_by_russian_roulette(&srec.attenuation))
		return (emmited);


	t_light_pdf		light_ = construct_light_pdf(rec, *world);
	t_mixture_pdf	mix_ = construct_mixture_pdf(srec.surface_pdf_ptr, &light_);

	t_vec3	scatter_direction = mix_.pdf.random_pdf(&mix_);
	t_ray	scattered = construct_ray(rec.p, scatter_direction);

	double	surface_pdf = rec.mat_ptr->value_surface_pdf(rec.mat_ptr, rec, scattered);
	double	sampling_pdf = mix_.pdf.value_pdf(&mix_, scatter_direction);
	t_color color_in = add_vec(emmited, scal_mul_vec(mul_vec(srec.attenuation, ray_color(scattered, world, depth + 1)), (surface_pdf / sampling_pdf)));
	free(srec.surface_pdf_ptr);
	return (color_in);
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
