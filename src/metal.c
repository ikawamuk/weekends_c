#include <stdlib.h>
#include "metal.h"
#include "rt_utils.h"

bool	scatter_metal(void *s, t_hit_record rec, t_scatter_record *srec);

t_metal	construct_metal(t_color alb, double fuzz)
{
	t_metal	metal;

	metal.material.scatter = scatter_metal;
	metal.material.emitted = emitted_non_light;
	metal.albedo = construct_color(alb.x, alb.y, alb.z);
	metal.fuzz = clamp(fuzz, 0.1, 0.9);
	return (metal);
}

bool	scatter_metal(void *s, t_hit_record rec, t_scatter_record *srec)
{
	t_metal	*self = s;

	t_vec3	reflect_normal = dot(rec.normal, rec.ray_in.direct) > 0 ? negative_vec(rec.normal) : rec.normal;
	t_vec3	reflected = reflect(normalize(rec.ray_in.direct), reflect_normal);
	srec->surface_pdf_ptr = 0;
	srec->attenuation = self->albedo;
	srec->is_specular = true;
	srec->specular_ray = construct_ray(rec.p, add_vec(reflected, scal_mul_vec(random_in_unit_sphere(), self->fuzz)));
	return (true);
}

t_metal	*gen_metal(t_color alb, double fuzz)
{
	t_metal	*p = malloc(sizeof(*p));
	if (!p)
		return (NULL);
	*p = construct_metal(alb, fuzz);
	return (p);
}