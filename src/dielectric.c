#include "dielectric.h"
#include <stdlib.h>

static bool	scatter_dielectric(void *s, t_hit_record *rec, t_scatter_record *srec);

t_dielectric	construct_dielectric(double refract_idx)
{
	t_dielectric	diel;

	diel.material.scatter = scatter_dielectric;
	diel.material.emitted = emitted_non_light;
	diel.refract_idx = refract_idx;
	return (diel);
}

t_dielectric	*gen_dielectric(double refract_idx)
{
	t_dielectric	*p = malloc(sizeof(*p));
	if (!p)
		return (NULL);
	*p = construct_dielectric(refract_idx);
	return (p);
}

static bool	scatter_dielectric(void *s, t_hit_record *rec, t_scatter_record *srec)
{
	t_dielectric	*self = s;

	t_vec3	outward_normal = dot(rec->ray_in.direct, rec->normal) < 0 ?  rec->normal : negative_vec(rec->normal);
	double	refract_ratio = dot(rec->ray_in.direct, rec->normal) < 0 ? (1.0 / self->refract_idx) : self->refract_idx;
	t_vec3	unit_direction = normalize(rec->ray_in.direct);

	
	double	cos_theta = fmin(dot(negative_vec(unit_direction), outward_normal), 1.0);
	double sin_theta = sqrt(1.0 - cos_theta*cos_theta);
	if (refract_ratio * sin_theta > 1.0)
		srec->specular_ray = construct_ray(rec->p, reflect(unit_direction, outward_normal));
	else
		srec->specular_ray = construct_ray(rec->p, refract(unit_direction, outward_normal, refract_ratio));
	srec->is_specular = true;
	srec->attenuation = construct_color(255,255,255);
	srec->surface_pdf_ptr = 0;
	
	return (true);
}
