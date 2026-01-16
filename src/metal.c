#include <stdlib.h>
#include "metal.h"
#include "rt_utils.h"
#include "texture.h"

bool	scatter_metal(void *s, t_hit_record *rec, t_scatter_record *srec);

t_metal	construct_metal(double fuzz)
{
	t_metal	metal;

	metal.material.scatter = scatter_metal;
	metal.material.emitted = emitted_non_light;
	metal.fuzz = clamp(fuzz, 0, 1.0);
	return (metal);
}

bool	scatter_metal(void *s, t_hit_record *rec, t_scatter_record *srec)
{
	t_metal	*self = s;

	srec->attenuation = rec->texture_p->texture_value(rec->texture_p, rec->u, rec->v, rec);
	t_vec3	reflect_normal = dot(rec->normal, rec->ray_in.direct) > 0 ? negative_vec(rec->normal) : rec->normal;
	t_vec3	reflected = reflect(normalize(rec->ray_in.direct), reflect_normal);
	srec->surface_pdf_ptr = 0;
	srec->is_specular = true;
	srec->specular_ray = construct_ray(rec->p, add_vec(reflected, scal_mul_vec(random_in_unit_sphere(), 0.5 *self->fuzz))); // 正規ベクトルに対してのばらつきだから * 0.3ぐらい
	return (true);
}

t_metal	*gen_metal(double fuzz)
{
	t_metal	*p = malloc(sizeof(*p));
	if (!p)
		return (NULL);
	*p = construct_metal(fuzz);
	return (p);
}