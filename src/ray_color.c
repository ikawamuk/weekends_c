#include "vec3.h"
#include "ray.h"
#include "hit_table_list.h"
#include "material.h"
#include "rt_utils.h"
#include "world.h"
#include "pdf.h"
#include "bvh.h"

static bool	killed_by_russian_roulette(t_color *attenuation);
static t_color caluculate_diffused_color(const t_world *world, t_hit_record rec, t_scatter_record srec, t_color emmited, int depth);

/*
@brief Color_i = Albedo * Color_o * surface_pdf / sampling_pdf; 
*/
t_color ray_color(t_ray ray, const t_world *world, int depth)
{
	t_hit_record	rec;
	t_range			range;

	range = construct_range(HIT_T_MIN, INFINITY);
	if (depth >= MAX_DEPTH)
		return (construct_vec(0, 0, 0));
	if (!world->node || world->node->hit(world->node, ray, &rec, range) == false)
		return (scal_mul_vec(world->back_ground, world->ambient_ratio));

	t_color	emmited = rec.mat_ptr->emitted(rec.mat_ptr, rec);

	t_scatter_record	srec;
	if (!rec.mat_ptr->scatter(rec.mat_ptr, &rec, &srec))
		return (emmited);
	if (depth > RR_START_DEPTH && killed_by_russian_roulette(&srec.attenuation))
		return (emmited);

	if (srec.is_specular)
		return (mul_vec(srec.attenuation, ray_color(srec.specular_ray, world, depth + 1))); // Color_i = albedo * Color_o

	t_color color_in = caluculate_diffused_color(world, rec, srec, emmited, depth);
	return (color_in);
}

static t_color caluculate_diffused_color(const t_world *world, t_hit_record rec, t_scatter_record srec, t_color emmited, int depth)
{
	t_mixture_pdf	mix_;
	t_light_pdf		light_ = construct_light_pdf(rec, *world);
	if (world->lights.head != NULL)
		mix_ = construct_mixture_pdf(srec.surface_pdf_ptr, &light_);
	else
		mix_ = construct_mixture_pdf(srec.surface_pdf_ptr, NULL); // 暫定的にlightがない場合NULLを渡しているがもっといい方法がありそう。

	
	t_vec3	scatter_direction = mix_.pdf.random_pdf(&mix_);
	t_ray	scattered = construct_ray(rec.p, scatter_direction);

	double	surface_pdf = rec.mat_ptr->value_surface_pdf(rec.mat_ptr, rec, scattered);
	double	sampling_pdf = mix_.pdf.value_pdf(&mix_, scatter_direction);
	t_color color_in = add_vec(emmited, scal_mul_vec(mul_vec(srec.attenuation, ray_color(scattered, world, depth + 1)), (surface_pdf / sampling_pdf)));
	// color_out = emmited + albedo * color_in * surface_pdf / sampling_pdf
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
