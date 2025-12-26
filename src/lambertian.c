#include <stdlib.h>
#include "lambertian.h"
#include "rt_utils.h"
#include "pdf.h"

t_lambertian	construct_lambertian(void *albedo_p)
{
	t_lambertian	lam;

	lam.material.scatter = scatter_lambertian;
	lam.material.emitted = emitted_non_light;
	lam.material.value_surface_pdf = lambertian_pdf;
	lam.albedo_p = albedo_p; // clear lambertianを実装しなきゃ！というかデストラクタですね
	return (lam);
}

/*
@brief 1.surface_PDFを代入 2.反射率Albedoを代入
*/
bool	scatter_lambertian(void *s, t_hit_record *rec, t_scatter_record *srec)
{
	t_lambertian	*self = s;

	srec->is_specular = false;
	srec->attenuation = self->albedo_p->texture_value(self->albedo_p, rec->u, rec->v, rec);

	t_vec3			reflect_normal = dot(rec->normal, rec->ray_in.direct) > 0 ? negative_vec(rec->normal) : rec->normal;
	t_cosine_pdf	*cos_ = generate_cosine_pdf(reflect_normal);

	srec->surface_pdf_ptr = cos_;
	return (true);
}

/*
@brief PDF = cosθ / π
*/
double	lambertian_pdf(void *s, t_hit_record rec, t_ray scattered)
{
	t_lambertian	*self = s;

	(void)self;
	t_cosine_pdf	cos_ = construct_cosine_pdf(rec.normal);
	double result = cos_.pdf.value_pdf(&cos_, scattered.direct);
	return (result < 0 ? 0 : result);
}

t_lambertian	*gen_lambertian(void *albedo_p)
{
	t_lambertian	*p = malloc(sizeof(*p));
	if (!p)
		return (NULL);
	*p = construct_lambertian(albedo_p);
	return (p);
}
